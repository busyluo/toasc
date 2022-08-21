#ifndef U_MESSAGE_H_
#define U_MESSAGE_H_

#include "utype.h"

typedef struct ffht {
    uint8_t reservedBit;              /* 1(true) or 0(false) */
    uint8_t payloadPreambleIndicator; /* 1(true) or 0(false) */
    uint8_t nullFrameIndicator;       /* 1(true) or 0(false) */
    uint8_t syncFrameIndicator;       /* 1(true) or 0(false) */
    uint8_t startupFrameIndicator;    /* 1(true) or 0(false) */
    uint16_t frameID;
    uint8_t cycleCount;
    uint8_t payloadLength;
    uint16_t headerCrc;
    uint16_t slotStatus;
} FlexrayFrameHeader_t;

/* FlexRay bus message data head */
typedef struct {
    FlexrayFrameHeader_t ffh; /* FlexRay frame header information */
    FR_PAYLOAD_t payload[0];  /* Pointer to payload data */
} UBusMessageFrDataHead_t;

/* CAN bus message data head */
typedef struct {
    /* Bit21: ID Extended, 1=Frame format is extended; 0=Frame format is standard;
     * Bit20: Remote Transmission Request, 1=Remote frame;
     */
    uint32_t cs;             /* Code and Status*/
    uint8_t payloadLength;   /* Length of data in bytes */
    CANPayload_t payload[0]; /* Data bytes of the CAN message*/
} UBusMessageCANDataHead_t;

/* Bus message data head */
typedef union {
    /* FlexRay message data */
    UBusMessageFrDataHead_t frData;
    /* CAN message data */
    UBusMessageCANDataHead_t canData;
    /* LIN message data */
    /* Todo */
} UBusMessageDataHead_t;

/* Bus message */
typedef struct {
    U_SERIAL_NUMBER serialNumber; /* Message serial number */
    uint64_t stamp;               /* Message stamp */
    /*
     * Stamp extension, different meaning for different message type
     * FR : Cycle counter
     * CAN:
     * LIN:
     */
    uint32_t stampExt;   /* Message stamp extended */
    uint8_t type;        /* Message type, reference to "UBusTypeIdEnum_t" */
    UBusNodeId_t nodeId; /* Node ID */

    UBusMessageDataHead_t data; /* Data head */
} UBusMessageHead_t;

#endif // U_MESSAGE_H_
