#pragma once
// MESSAGE BELUGA_PN_SN PACKING

#define MAVLINK_MSG_ID_BELUGA_PN_SN 60000


typedef struct __mavlink_beluga_pn_sn_t {
 char PN[10]; /*<  PN*/
 char SN[10]; /*<  SN*/
} mavlink_beluga_pn_sn_t;

#define MAVLINK_MSG_ID_BELUGA_PN_SN_LEN 20
#define MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN 20
#define MAVLINK_MSG_ID_60000_LEN 20
#define MAVLINK_MSG_ID_60000_MIN_LEN 20

#define MAVLINK_MSG_ID_BELUGA_PN_SN_CRC 181
#define MAVLINK_MSG_ID_60000_CRC 181

#define MAVLINK_MSG_BELUGA_PN_SN_FIELD_PN_LEN 10
#define MAVLINK_MSG_BELUGA_PN_SN_FIELD_SN_LEN 10

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_BELUGA_PN_SN { \
    60000, \
    "BELUGA_PN_SN", \
    2, \
    {  { "PN", NULL, MAVLINK_TYPE_CHAR, 10, 0, offsetof(mavlink_beluga_pn_sn_t, PN) }, \
         { "SN", NULL, MAVLINK_TYPE_CHAR, 10, 10, offsetof(mavlink_beluga_pn_sn_t, SN) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_BELUGA_PN_SN { \
    "BELUGA_PN_SN", \
    2, \
    {  { "PN", NULL, MAVLINK_TYPE_CHAR, 10, 0, offsetof(mavlink_beluga_pn_sn_t, PN) }, \
         { "SN", NULL, MAVLINK_TYPE_CHAR, 10, 10, offsetof(mavlink_beluga_pn_sn_t, SN) }, \
         } \
}
#endif

/**
 * @brief Pack a beluga_pn_sn message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param PN  PN
 * @param SN  SN
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_beluga_pn_sn_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const char *PN, const char *SN)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BELUGA_PN_SN_LEN];

    _mav_put_char_array(buf, 0, PN, 10);
    _mav_put_char_array(buf, 10, SN, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN);
#else
    mavlink_beluga_pn_sn_t packet;

    mav_array_memcpy(packet.PN, PN, sizeof(char)*10);
    mav_array_memcpy(packet.SN, SN, sizeof(char)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BELUGA_PN_SN;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_CRC);
}

/**
 * @brief Pack a beluga_pn_sn message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param PN  PN
 * @param SN  SN
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_beluga_pn_sn_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const char *PN,const char *SN)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BELUGA_PN_SN_LEN];

    _mav_put_char_array(buf, 0, PN, 10);
    _mav_put_char_array(buf, 10, SN, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN);
#else
    mavlink_beluga_pn_sn_t packet;

    mav_array_memcpy(packet.PN, PN, sizeof(char)*10);
    mav_array_memcpy(packet.SN, SN, sizeof(char)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BELUGA_PN_SN;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_CRC);
}

/**
 * @brief Encode a beluga_pn_sn struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param beluga_pn_sn C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_beluga_pn_sn_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_beluga_pn_sn_t* beluga_pn_sn)
{
    return mavlink_msg_beluga_pn_sn_pack(system_id, component_id, msg, beluga_pn_sn->PN, beluga_pn_sn->SN);
}

/**
 * @brief Encode a beluga_pn_sn struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param beluga_pn_sn C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_beluga_pn_sn_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_beluga_pn_sn_t* beluga_pn_sn)
{
    return mavlink_msg_beluga_pn_sn_pack_chan(system_id, component_id, chan, msg, beluga_pn_sn->PN, beluga_pn_sn->SN);
}

/**
 * @brief Send a beluga_pn_sn message
 * @param chan MAVLink channel to send the message
 *
 * @param PN  PN
 * @param SN  SN
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_beluga_pn_sn_send(mavlink_channel_t chan, const char *PN, const char *SN)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BELUGA_PN_SN_LEN];

    _mav_put_char_array(buf, 0, PN, 10);
    _mav_put_char_array(buf, 10, SN, 10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BELUGA_PN_SN, buf, MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_CRC);
#else
    mavlink_beluga_pn_sn_t packet;

    mav_array_memcpy(packet.PN, PN, sizeof(char)*10);
    mav_array_memcpy(packet.SN, SN, sizeof(char)*10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BELUGA_PN_SN, (const char *)&packet, MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_CRC);
#endif
}

/**
 * @brief Send a beluga_pn_sn message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_beluga_pn_sn_send_struct(mavlink_channel_t chan, const mavlink_beluga_pn_sn_t* beluga_pn_sn)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_beluga_pn_sn_send(chan, beluga_pn_sn->PN, beluga_pn_sn->SN);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BELUGA_PN_SN, (const char *)beluga_pn_sn, MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_CRC);
#endif
}

#if MAVLINK_MSG_ID_BELUGA_PN_SN_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_beluga_pn_sn_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *PN, const char *SN)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_char_array(buf, 0, PN, 10);
    _mav_put_char_array(buf, 10, SN, 10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BELUGA_PN_SN, buf, MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_CRC);
#else
    mavlink_beluga_pn_sn_t *packet = (mavlink_beluga_pn_sn_t *)msgbuf;

    mav_array_memcpy(packet->PN, PN, sizeof(char)*10);
    mav_array_memcpy(packet->SN, SN, sizeof(char)*10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BELUGA_PN_SN, (const char *)packet, MAVLINK_MSG_ID_BELUGA_PN_SN_MIN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN, MAVLINK_MSG_ID_BELUGA_PN_SN_CRC);
#endif
}
#endif

#endif

// MESSAGE BELUGA_PN_SN UNPACKING


/**
 * @brief Get field PN from beluga_pn_sn message
 *
 * @return  PN
 */
static inline uint16_t mavlink_msg_beluga_pn_sn_get_PN(const mavlink_message_t* msg, char *PN)
{
    return _MAV_RETURN_char_array(msg, PN, 10,  0);
}

/**
 * @brief Get field SN from beluga_pn_sn message
 *
 * @return  SN
 */
static inline uint16_t mavlink_msg_beluga_pn_sn_get_SN(const mavlink_message_t* msg, char *SN)
{
    return _MAV_RETURN_char_array(msg, SN, 10,  10);
}

/**
 * @brief Decode a beluga_pn_sn message into a struct
 *
 * @param msg The message to decode
 * @param beluga_pn_sn C-struct to decode the message contents into
 */
static inline void mavlink_msg_beluga_pn_sn_decode(const mavlink_message_t* msg, mavlink_beluga_pn_sn_t* beluga_pn_sn)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_beluga_pn_sn_get_PN(msg, beluga_pn_sn->PN);
    mavlink_msg_beluga_pn_sn_get_SN(msg, beluga_pn_sn->SN);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_BELUGA_PN_SN_LEN? msg->len : MAVLINK_MSG_ID_BELUGA_PN_SN_LEN;
        memset(beluga_pn_sn, 0, MAVLINK_MSG_ID_BELUGA_PN_SN_LEN);
    memcpy(beluga_pn_sn, _MAV_PAYLOAD(msg), len);
#endif
}
