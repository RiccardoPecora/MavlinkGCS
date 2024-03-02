/** @file
 *	@brief MAVLink comm testsuite protocol generated from beluga.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "beluga.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(beluga, BELUGA_PN_SN)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::beluga::msg::BELUGA_PN_SN packet_in{};
    packet_in.PN = to_char_array("ABCDEFGHI");
    packet_in.SN = to_char_array("KLMNOPQRS");

    mavlink::beluga::msg::BELUGA_PN_SN packet1{};
    mavlink::beluga::msg::BELUGA_PN_SN packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.PN, packet2.PN);
    EXPECT_EQ(packet1.SN, packet2.SN);
}

#ifdef TEST_INTEROP
TEST(beluga_interop, BELUGA_PN_SN)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_beluga_pn_sn_t packet_c {
         "ABCDEFGHI", "KLMNOPQRS"
    };

    mavlink::beluga::msg::BELUGA_PN_SN packet_in{};
    packet_in.PN = to_char_array("ABCDEFGHI");
    packet_in.SN = to_char_array("KLMNOPQRS");

    mavlink::beluga::msg::BELUGA_PN_SN packet2{};

    mavlink_msg_beluga_pn_sn_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.PN, packet2.PN);
    EXPECT_EQ(packet_in.SN, packet2.SN);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
