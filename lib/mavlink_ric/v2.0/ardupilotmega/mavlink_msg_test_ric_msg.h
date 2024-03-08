#pragma once
// MESSAGE TEST_RIC_MSG PACKING

#define MAVLINK_MSG_ID_TEST_RIC_MSG 11040


typedef struct __mavlink_test_ric_msg_t {
 uint16_t id; /*<  TEST RIC instance*/
 int16_t TEST_RIC_value; /*<  TEST RIC value*/
} mavlink_test_ric_msg_t;

#define MAVLINK_MSG_ID_TEST_RIC_MSG_LEN 4
#define MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN 4
#define MAVLINK_MSG_ID_11040_LEN 4
#define MAVLINK_MSG_ID_11040_MIN_LEN 4

#define MAVLINK_MSG_ID_TEST_RIC_MSG_CRC 219
#define MAVLINK_MSG_ID_11040_CRC 219



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TEST_RIC_MSG { \
    11040, \
    "TEST_RIC_MSG", \
    2, \
    {  { "id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_test_ric_msg_t, id) }, \
         { "TEST_RIC_value", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_test_ric_msg_t, TEST_RIC_value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TEST_RIC_MSG { \
    "TEST_RIC_MSG", \
    2, \
    {  { "id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_test_ric_msg_t, id) }, \
         { "TEST_RIC_value", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_test_ric_msg_t, TEST_RIC_value) }, \
         } \
}
#endif

/**
 * @brief Pack a test_ric_msg message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id  TEST RIC instance
 * @param TEST_RIC_value  TEST RIC value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_ric_msg_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t id, int16_t TEST_RIC_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_RIC_MSG_LEN];
    _mav_put_uint16_t(buf, 0, id);
    _mav_put_int16_t(buf, 2, TEST_RIC_value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN);
#else
    mavlink_test_ric_msg_t packet;
    packet.id = id;
    packet.TEST_RIC_value = TEST_RIC_value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TEST_RIC_MSG;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_CRC);
}

/**
 * @brief Pack a test_ric_msg message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id  TEST RIC instance
 * @param TEST_RIC_value  TEST RIC value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_ric_msg_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t id,int16_t TEST_RIC_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_RIC_MSG_LEN];
    _mav_put_uint16_t(buf, 0, id);
    _mav_put_int16_t(buf, 2, TEST_RIC_value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN);
#else
    mavlink_test_ric_msg_t packet;
    packet.id = id;
    packet.TEST_RIC_value = TEST_RIC_value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TEST_RIC_MSG;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_CRC);
}

/**
 * @brief Encode a test_ric_msg struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param test_ric_msg C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_test_ric_msg_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_test_ric_msg_t* test_ric_msg)
{
    return mavlink_msg_test_ric_msg_pack(system_id, component_id, msg, test_ric_msg->id, test_ric_msg->TEST_RIC_value);
}

/**
 * @brief Encode a test_ric_msg struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param test_ric_msg C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_test_ric_msg_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_test_ric_msg_t* test_ric_msg)
{
    return mavlink_msg_test_ric_msg_pack_chan(system_id, component_id, chan, msg, test_ric_msg->id, test_ric_msg->TEST_RIC_value);
}

/**
 * @brief Send a test_ric_msg message
 * @param chan MAVLink channel to send the message
 *
 * @param id  TEST RIC instance
 * @param TEST_RIC_value  TEST RIC value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_test_ric_msg_send(mavlink_channel_t chan, uint16_t id, int16_t TEST_RIC_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_RIC_MSG_LEN];
    _mav_put_uint16_t(buf, 0, id);
    _mav_put_int16_t(buf, 2, TEST_RIC_value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST_RIC_MSG, buf, MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_CRC);
#else
    mavlink_test_ric_msg_t packet;
    packet.id = id;
    packet.TEST_RIC_value = TEST_RIC_value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST_RIC_MSG, (const char *)&packet, MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_CRC);
#endif
}

/**
 * @brief Send a test_ric_msg message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_test_ric_msg_send_struct(mavlink_channel_t chan, const mavlink_test_ric_msg_t* test_ric_msg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_test_ric_msg_send(chan, test_ric_msg->id, test_ric_msg->TEST_RIC_value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST_RIC_MSG, (const char *)test_ric_msg, MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_CRC);
#endif
}

#if MAVLINK_MSG_ID_TEST_RIC_MSG_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_test_ric_msg_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t id, int16_t TEST_RIC_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, id);
    _mav_put_int16_t(buf, 2, TEST_RIC_value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST_RIC_MSG, buf, MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_CRC);
#else
    mavlink_test_ric_msg_t *packet = (mavlink_test_ric_msg_t *)msgbuf;
    packet->id = id;
    packet->TEST_RIC_value = TEST_RIC_value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST_RIC_MSG, (const char *)packet, MAVLINK_MSG_ID_TEST_RIC_MSG_MIN_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN, MAVLINK_MSG_ID_TEST_RIC_MSG_CRC);
#endif
}
#endif

#endif

// MESSAGE TEST_RIC_MSG UNPACKING


/**
 * @brief Get field id from test_ric_msg message
 *
 * @return  TEST RIC instance
 */
static inline uint16_t mavlink_msg_test_ric_msg_get_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field TEST_RIC_value from test_ric_msg message
 *
 * @return  TEST RIC value
 */
static inline int16_t mavlink_msg_test_ric_msg_get_TEST_RIC_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Decode a test_ric_msg message into a struct
 *
 * @param msg The message to decode
 * @param test_ric_msg C-struct to decode the message contents into
 */
static inline void mavlink_msg_test_ric_msg_decode(const mavlink_message_t* msg, mavlink_test_ric_msg_t* test_ric_msg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    test_ric_msg->id = mavlink_msg_test_ric_msg_get_id(msg);
    test_ric_msg->TEST_RIC_value = mavlink_msg_test_ric_msg_get_TEST_RIC_value(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TEST_RIC_MSG_LEN? msg->len : MAVLINK_MSG_ID_TEST_RIC_MSG_LEN;
        memset(test_ric_msg, 0, MAVLINK_MSG_ID_TEST_RIC_MSG_LEN);
    memcpy(test_ric_msg, _MAV_PAYLOAD(msg), len);
#endif
}
