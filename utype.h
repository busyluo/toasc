#ifndef U_TYPE_H_
#define U_TYPE_H_

#include <cstdint>


#define UBS_FLAG_CALLED_FROM_ISR  (0x00000001)

/*
 * Ulan Control & Status bit defines
 */
/* Control bits mask */
#define UCS_CTRL_BITS_MASK      (0xFFFF0000U)
/* Global enable */
#define UCS_GLOBAL_EN           (0x80000000U)
/* Offline enable */
#define UCS_OFFLINE_EN          (0x40000000U)
/* Upload enable */
#define UCS_UPLOAD_EN           (0x20000000U)
/* Record enable */
#define UCS_RECORD_EN           (0x10000000U)
/* Node config saving enable */
#define UCS_NODE_CFG_SAVING_EN  (0x08000000U)
/* Started */
#define UCS_STARTED             (0x00008000U)
/* Linked */
#define UCS_LINKED              (0x00004000U)

/*
 * Event bit defines
 */
#define EVT_SYS_START             (0x00000001U)
#define EVT_SYS_STOP              (0x00000002U)
#define EVT_SYS_START_UPLOADING   (0x00000004U)
#define EVT_SYS_STOP_UPLOADING    (0x00000008U)
#define EVT_SYS_START_RECORDING   (0x00000010U)
#define EVT_SYS_STOP_RECORDING    (0x00000020U)
#define EVT_FR_CYCLE_START        (0x00010000U)
#define EVT_FR_REPLAY_DATA_READY  (0x00020000U)

/*
 * Endian process
 */
#define ENDIAN_SWAP_64(n)    {(n)=((((n) & 0xFF) << 56) | (((n) & 0xFF00) << 40) | (((n) & 0xFF0000) << 24) | (((n) & 0xFF000000) << 8) | \
									(((n) & 0xFF00000000) >> 8) | (((n) & 0xFF0000000000) >> 24) | (((n) & 0xFF000000000000) >> 40) | (((n) & 0xFF00000000000000) >> 56));}
#define ENDIAN_SWAP_32(n)    {(n)=((((n) & 0xFF) << 24) | (((n) & 0xFF00) << 8) | (((n) & 0xFF0000) >> 8) | (((n) & 0xFF000000) >> 24));}
#define ENDIAN_SWAP_16(n)    {(n)=((((n) & 0xFF) << 8) | (((n) & 0xFF00) >> 8));}
#define ENDIAN_SWAP_8(n)     (n)

/*
 * Data type definitions
 */
/* Node working mode */
typedef enum
{
	NWM_NONE = 0U,
	NWM_GENERAL,
	NWM_MONITOR,
	NWM_REPLAY,
} NodeWorkingMode_t;

/* Bus type */
typedef enum
{
	UBT_NONE = 0U,
	UBT_FLEXRAY,
	UBT_CAN,
	UBT_LIN,
} UBusTypeIdEnum_t;

/* device open count type */
typedef uint8_t DEVICE_OPEN_COUNT_t;

/* Serial number */
typedef uint32_t U_SERIAL_NUMBER;

/* Time stamp */
typedef uint32_t U_TIME_STAMP; /* Temporarily */

/* command type */
typedef uint8_t UCOMMAND_t;
/* command execution status type */
typedef uint8_t UCOMMAND_STATUS_t;

/* Bus type identifier */
typedef uint8_t UBusTypeId_t;

/* controller number type *//* Obsoleted, use bus node id and interface id instead of this */
typedef uint8_t CONTROLLER_NUM_t;
/* Bus node index number type */
typedef uint8_t UBusNodeId_t;
/* Bus interface index number type */
typedef uint8_t UBusInterfaceId_t;

/* Time stamp structure */
typedef struct
{
	uint64_t microseconds;
	/* Time stamp extension with different meaning for different scenarios */
	/* Cycle offset for FlexRay message */
	uint32_t extension;
} UTimestamp_t;

/* FlexRay slot ID type */
typedef uint16_t FR_SLOT_ID_t;
/* Message buffer ID type */
typedef uint8_t MessageBufferID_t;
/* FlexRay payload length type (number of two-byte words) */
typedef uint8_t FR_PAYLOAD_LEN_t;
/* FlexRay payload type */
typedef uint16_t FR_PAYLOAD_t;

/* CAN payload type */
typedef uint8_t CANPayload_t;

/*
 * Constant definitions
 */
#define MSG_BUFFER_ID_AUTO  ((MessageBufferID_t)(~(0ULL)))


#endif /* U_TYPE_H_ */
