#include "converter.h"
#include <QFile>
#include "Vector_ASC/src/Vector/ASC.h"
#include "umessage.h"

using namespace Vector::ASC;

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

    QStringList path_items = input.split("/");
    QString asc_name = path_items.last().split(".").front();
    QString file_dir = path_items.mid(0, path_items.size() - 1).join("/");
    //    UBusMessageHead_t message_head;
    //    memcpy(&message_head, urc_data.data() + data_ptr, k_msg_head_size);
    //    if (message_head.type == UBT_FLEXRAY) {
    //    } else if (message_head.type == UBT_CAN) {
    //    }

    Vector::ASC::File asc_file;
    QString asc_file_name = file_dir + "/" + asc_name + ".asc";
    asc_file.open(asc_file_name.toStdString(), File::OpenMode::Write);
    if (!asc_file.is_open()) {
        emit Failed("打开asc文件失败");
        return;
    }
    FileDate date;
    time_t now;
    time(&now);
    struct tm tm = *localtime(&now);
    date.date = tm;
    asc_file.write(&date);

    FileBaseTimestamps base;
    asc_file.write(&base);

    FileInternalEventsLogged logged;
    asc_file.write(&logged);

    FileVersion version;
    version.versionMajor = 8;
    version.versionMinor = 1;
    version.versionPatch = 0;
    asc_file.write(&version);

    BeginTriggerblock begin;
    begin.date = tm;
    asc_file.write(&begin);

    while (data_ptr < urc_data.size()) {
        UBusMessageHead_t message_head;
        memcpy(&message_head, urc_data.data() + data_ptr, k_msg_head_size);
        data_ptr += k_msg_head_size;

        uint8_t payload_len;
        if (message_head.type == UBT_FLEXRAY) {
            memcpy(&message_head.data, urc_data.data() + data_ptr, k_fr_head_size);
            data_ptr += k_fr_head_size;

            payload_len = message_head.data.frData.ffh.payloadLength * sizeof(FR_PAYLOAD_t);
            std::vector<Dx> fr_data(payload_len);
            memcpy(fr_data.data(), urc_data.data() + data_ptr, payload_len);
            data_ptr += payload_len;

            FlexRayMessage msg;
            msg.time = message_head.stamp / 1000000.0;
            msg.data = fr_data;
            msg.clusterNr = 0;
            msg.clientId = 0;
            msg.channelNr = 1;
            if (message_head.data.frData.ffh.slotStatus & 0x80) {
                msg.channelMask = 1;
            } else {
                msg.channelMask = 2;
            }
            msg.slotId = message_head.data.frData.ffh.frameID;
            msg.cycleNo = message_head.data.frData.ffh.cycleCount;
            msg.ccType = 5;
            msg.ccData = message_head.data.frData.ffh.slotStatus;
            msg.headerCrc = message_head.data.frData.ffh.headerCrc;
            msg.name = "xxxx";
            msg.payloadLength = message_head.data.frData.ffh.payloadLength;
            msg.bufferLength = message_head.data.frData.ffh.payloadLength;
            msg.frameCrc = 0;
            msg.spyFlag = 0;
            msg.frameLengthNs = 0;
            msg.pduOffset = 0;
            asc_file.write(&msg);
        } else if (message_head.type == UBT_CAN) {
            memcpy(&message_head.data, urc_data.data() + data_ptr, k_can_head_size);
            data_ptr += k_can_head_size - 3;

            payload_len = message_head.data.canData.payloadLength * sizeof(CANPayload_t);
            std::vector<Dx> can_data(payload_len);
            memcpy(can_data.data(), urc_data.data() + data_ptr, payload_len);
            data_ptr += payload_len;
            data_ptr += 3;

            if (message_head.data.canData.cs >> 21 & 0x01) {
                CanExtendedMessage msg;
                msg.id = message_head.data.canData.messageId;
                msg.channel = message_head.nodeId;
                msg.dir = Dir::Rx;
                msg.dlc = payload_len;
                msg.time = message_head.stamp / 1000000.0;
                msg.data = can_data;
                asc_file.write(&msg);
            } else if (message_head.data.canData.cs >> 20 & 0x01) {
                CanRemoteFrame msg;
                msg.id = message_head.data.canData.messageId;
                msg.channel = message_head.nodeId;
                msg.dir = Dir::Rx;
                msg.time = message_head.stamp / 1000000.0;
                asc_file.write(&msg);
            } else {
                CanMessage msg;
                msg.id = message_head.data.canData.messageId;
                msg.channel = message_head.nodeId;
                msg.dir = Dir::Rx;
                msg.dlc = payload_len;
                msg.time = message_head.stamp / 1000000.0;
                msg.data = can_data;
                asc_file.write(&msg);
            }
        } else {
            emit Failed(QString("不支持的总线类型: %1").arg(message_head.type));
            return;
        }
    }

    EndTriggerblock end;
    asc_file.write(&end);

    asc_file.close();

    emit Progress(100);
}
