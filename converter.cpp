#include "converter.h"
#include <QFile>
#include "umessage.h"

Converter::Converter(QObject* parent) : QObject(parent) {
}

void Converter::Convert(QString input) {
    emit Started();

    QFile file(input);
    if (!file.open(QFile::ReadOnly)) {
        emit Failed("打开文件失败");
        return;
    }
    emit Progress(1);

    QByteArray urc_data = file.readAll();

    uint64_t data_ptr = 0x20;

    const uint8_t k_msg_head_size = sizeof(UBusMessageHead_t) - sizeof(UBusMessageDataHead_t);
    const uint8_t k_fr_head_size = sizeof(UBusMessageFrDataHead_t);
    const uint8_t k_can_head_size = sizeof(UBusMessageCANDataHead_t);
    while (data_ptr < urc_data.size()) {
        UBusMessageHead_t message_head;
        memcpy(&message_head, urc_data.data() + data_ptr, k_msg_head_size);
        data_ptr += k_msg_head_size;

        uint8_t payload_len;
        if (message_head.type == UBT_FLEXRAY) {
            memcpy(&message_head.data, urc_data.data() + data_ptr, k_fr_head_size);
            data_ptr += k_fr_head_size;

            payload_len = message_head.data.frData.ffh.payloadLength * sizeof(FR_PAYLOAD_t);
            data_ptr += payload_len;
        } else if (message_head.type == UBT_CAN) {
            memcpy(&message_head.data, urc_data.data() + data_ptr, k_can_head_size);
            data_ptr += k_can_head_size;

            payload_len = message_head.data.canData.payloadLength * sizeof(CANPayload_t);
            data_ptr += payload_len;
        } else {
            emit Failed(QString("不支持的总线类型: %1").arg(message_head.type));
            return;
        }
    }

    emit Progress(100);
}
