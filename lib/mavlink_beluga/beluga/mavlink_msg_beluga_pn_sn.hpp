// MESSAGE BELUGA_PN_SN support class

#pragma once

namespace mavlink {
namespace beluga {
namespace msg {

/**
 * @brief BELUGA_PN_SN message
 *
 * The Beluga Part Number and Serial Number.
 */
struct BELUGA_PN_SN : mavlink::Message {
    static constexpr msgid_t MSG_ID = 60000;
    static constexpr size_t LENGTH = 20;
    static constexpr size_t MIN_LENGTH = 20;
    static constexpr uint8_t CRC_EXTRA = 181;
    static constexpr auto NAME = "BELUGA_PN_SN";


    std::array<char, 10> PN; /*<  PN */
    std::array<char, 10> SN; /*<  SN */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  PN: \"" << to_string(PN) << "\"" << std::endl;
        ss << "  SN: \"" << to_string(SN) << "\"" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << PN;                            // offset: 0
        map << SN;                            // offset: 10
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> PN;                            // offset: 0
        map >> SN;                            // offset: 10
    }
};

} // namespace msg
} // namespace beluga
} // namespace mavlink
