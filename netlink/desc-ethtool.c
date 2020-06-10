/*
 * desc-ethtool.c - ethtool netlink format descriptions
 *
 * Descriptions of ethtool netlink messages and attributes for pretty print.
 */

#include "../internal.h"
#include <linux/ethtool_netlink.h>

#include "prettymsg.h"

static const struct pretty_nla_desc __header_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_HEADER_UNSPEC),
	NLATTR_DESC_U32(ETHTOOL_A_HEADER_DEV_INDEX),
	NLATTR_DESC_STRING(ETHTOOL_A_HEADER_DEV_NAME),
	NLATTR_DESC_X32(ETHTOOL_A_HEADER_FLAGS),
};

static const struct pretty_nla_desc __bitset_bit_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_BITSET_BIT_UNSPEC),
	NLATTR_DESC_U32(ETHTOOL_A_BITSET_BIT_INDEX),
	NLATTR_DESC_STRING(ETHTOOL_A_BITSET_BIT_NAME),
	NLATTR_DESC_FLAG(ETHTOOL_A_BITSET_BIT_VALUE),
};

static const struct pretty_nla_desc __bitset_bits_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_BITSET_BITS_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_BITSET_BITS_BIT, bitset_bit),
};

static const struct pretty_nla_desc __bitset_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_BITSET_UNSPEC),
	NLATTR_DESC_FLAG(ETHTOOL_A_BITSET_NOMASK),
	NLATTR_DESC_U32(ETHTOOL_A_BITSET_SIZE),
	NLATTR_DESC_NESTED(ETHTOOL_A_BITSET_BITS, bitset_bits),
	NLATTR_DESC_BINARY(ETHTOOL_A_BITSET_VALUE),
	NLATTR_DESC_BINARY(ETHTOOL_A_BITSET_MASK),
};

static const struct pretty_nla_desc __string_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_STRING_UNSPEC),
	NLATTR_DESC_U32(ETHTOOL_A_STRING_INDEX),
	NLATTR_DESC_STRING(ETHTOOL_A_STRING_VALUE),
};

static const struct pretty_nla_desc __strings_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_STRINGS_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_STRINGS_STRING, string),
};

static const struct pretty_nla_desc __stringset_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_STRINGSET_UNSPEC),
	NLATTR_DESC_U32(ETHTOOL_A_STRINGSET_ID),
	NLATTR_DESC_U32(ETHTOOL_A_STRINGSET_COUNT),
	NLATTR_DESC_NESTED(ETHTOOL_A_STRINGSET_STRINGS, strings),
};

static const struct pretty_nla_desc __stringsets_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_STRINGSETS_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_STRINGSETS_STRINGSET, stringset),
};

static const struct pretty_nla_desc __strset_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_STRSET_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_STRSET_HEADER, header),
	NLATTR_DESC_NESTED(ETHTOOL_A_STRSET_STRINGSETS, stringsets),
	NLATTR_DESC_FLAG(ETHTOOL_A_STRSET_COUNTS_ONLY),
};

static const struct pretty_nla_desc __linkinfo_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_LINKINFO_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_LINKINFO_HEADER, header),
	NLATTR_DESC_U8(ETHTOOL_A_LINKINFO_PORT),
	NLATTR_DESC_U8(ETHTOOL_A_LINKINFO_PHYADDR),
	NLATTR_DESC_U8(ETHTOOL_A_LINKINFO_TP_MDIX),
	NLATTR_DESC_U8(ETHTOOL_A_LINKINFO_TP_MDIX_CTRL),
	NLATTR_DESC_U8(ETHTOOL_A_LINKINFO_TRANSCEIVER),
};

static const struct pretty_nla_desc __linkmodes_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_LINKMODES_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_LINKMODES_HEADER, header),
	NLATTR_DESC_BOOL(ETHTOOL_A_LINKMODES_AUTONEG),
	NLATTR_DESC_NESTED(ETHTOOL_A_LINKMODES_OURS, bitset),
	NLATTR_DESC_NESTED(ETHTOOL_A_LINKMODES_PEER, bitset),
	NLATTR_DESC_U32(ETHTOOL_A_LINKMODES_SPEED),
	NLATTR_DESC_U8(ETHTOOL_A_LINKMODES_DUPLEX),
	NLATTR_DESC_U8(ETHTOOL_A_LINKMODES_MASTER_SLAVE_CFG),
	NLATTR_DESC_U8(ETHTOOL_A_LINKMODES_MASTER_SLAVE_STATE),
};

static const struct pretty_nla_desc __linkstate_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_LINKSTATE_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_LINKSTATE_HEADER, header),
	NLATTR_DESC_BOOL(ETHTOOL_A_LINKSTATE_LINK),
};

static const struct pretty_nla_desc __debug_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_DEBUG_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_DEBUG_HEADER, header),
	NLATTR_DESC_NESTED(ETHTOOL_A_DEBUG_MSGMASK, bitset),
};

static const struct pretty_nla_desc __wol_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_WOL_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_WOL_HEADER, header),
	NLATTR_DESC_NESTED(ETHTOOL_A_WOL_MODES, bitset),
	NLATTR_DESC_BINARY(ETHTOOL_A_WOL_SOPASS),
};

static const struct pretty_nla_desc __features_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_FEATURES_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_FEATURES_HEADER, header),
	NLATTR_DESC_NESTED(ETHTOOL_A_FEATURES_HW, bitset),
	NLATTR_DESC_NESTED(ETHTOOL_A_FEATURES_WANTED, bitset),
	NLATTR_DESC_NESTED(ETHTOOL_A_FEATURES_ACTIVE, bitset),
	NLATTR_DESC_NESTED(ETHTOOL_A_FEATURES_NOCHANGE, bitset),
};

static const struct pretty_nla_desc __privflags_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_PRIVFLAGS_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_PRIVFLAGS_HEADER, header),
	NLATTR_DESC_NESTED(ETHTOOL_A_PRIVFLAGS_FLAGS, bitset),
};

static const struct pretty_nla_desc __rings_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_RINGS_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_RINGS_HEADER, header),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_RX_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_RX_MINI_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_RX_JUMBO_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_TX_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_RX),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_RX_MINI),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_RX_JUMBO),
	NLATTR_DESC_U32(ETHTOOL_A_RINGS_TX),
};

static const struct pretty_nla_desc __channels_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_CHANNELS_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_CHANNELS_HEADER, header),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_RX_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_TX_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_OTHER_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_COMBINED_MAX),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_RX_COUNT),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_TX_COUNT),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_OTHER_COUNT),
	NLATTR_DESC_U32(ETHTOOL_A_CHANNELS_COMBINED_COUNT),
};

static const struct pretty_nla_desc __coalesce_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_COALESCE_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_COALESCE_HEADER, header),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_USECS),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_MAX_FRAMES),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_USECS_IRQ),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_MAX_FRAMES_IRQ),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_USECS),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_MAX_FRAMES),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_USECS_IRQ),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_MAX_FRAMES_IRQ),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_STATS_BLOCK_USECS),
	NLATTR_DESC_BOOL(ETHTOOL_A_COALESCE_USE_ADAPTIVE_RX),
	NLATTR_DESC_BOOL(ETHTOOL_A_COALESCE_USE_ADAPTIVE_TX),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_PKT_RATE_LOW),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_USECS_LOW),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_MAX_FRAMES_LOW),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_USECS_LOW),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_MAX_FRAMES_LOW),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_PKT_RATE_HIGH),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_USECS_HIGH),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RX_MAX_FRAMES_HIGH),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_USECS_HIGH),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_TX_MAX_FRAMES_HIGH),
	NLATTR_DESC_U32(ETHTOOL_A_COALESCE_RATE_SAMPLE_INTERVAL),
};

static const struct pretty_nla_desc __pause_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_PAUSE_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_PAUSE_HEADER, header),
	NLATTR_DESC_BOOL(ETHTOOL_A_PAUSE_AUTONEG),
	NLATTR_DESC_BOOL(ETHTOOL_A_PAUSE_RX),
	NLATTR_DESC_BOOL(ETHTOOL_A_PAUSE_TX),
};

static const struct pretty_nla_desc __eee_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_EEE_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_EEE_HEADER, header),
	NLATTR_DESC_NESTED(ETHTOOL_A_EEE_MODES_OURS, bitset),
	NLATTR_DESC_NESTED(ETHTOOL_A_EEE_MODES_PEER, bitset),
	NLATTR_DESC_BOOL(ETHTOOL_A_EEE_ACTIVE),
	NLATTR_DESC_BOOL(ETHTOOL_A_EEE_ENABLED),
	NLATTR_DESC_BOOL(ETHTOOL_A_EEE_TX_LPI_ENABLED),
	NLATTR_DESC_U32(ETHTOOL_A_EEE_TX_LPI_TIMER),
};

static const struct pretty_nla_desc __tsinfo_desc[] = {
	NLATTR_DESC_INVALID(ETHTOOL_A_TSINFO_UNSPEC),
	NLATTR_DESC_NESTED(ETHTOOL_A_TSINFO_HEADER, header),
	NLATTR_DESC_NESTED(ETHTOOL_A_TSINFO_TIMESTAMPING, bitset),
	NLATTR_DESC_NESTED(ETHTOOL_A_TSINFO_TX_TYPES, bitset),
	NLATTR_DESC_NESTED(ETHTOOL_A_TSINFO_RX_FILTERS, bitset),
	NLATTR_DESC_U32(ETHTOOL_A_TSINFO_PHC_INDEX),
};

const struct pretty_nlmsg_desc ethnl_umsg_desc[] = {
	NLMSG_DESC_INVALID(ETHTOOL_MSG_USER_NONE),
	NLMSG_DESC(ETHTOOL_MSG_STRSET_GET, strset),
	NLMSG_DESC(ETHTOOL_MSG_LINKINFO_GET, linkinfo),
	NLMSG_DESC(ETHTOOL_MSG_LINKINFO_SET, linkinfo),
	NLMSG_DESC(ETHTOOL_MSG_LINKMODES_GET, linkmodes),
	NLMSG_DESC(ETHTOOL_MSG_LINKMODES_SET, linkmodes),
	NLMSG_DESC(ETHTOOL_MSG_LINKSTATE_GET, linkstate),
	NLMSG_DESC(ETHTOOL_MSG_DEBUG_GET, debug),
	NLMSG_DESC(ETHTOOL_MSG_DEBUG_SET, debug),
	NLMSG_DESC(ETHTOOL_MSG_WOL_GET, wol),
	NLMSG_DESC(ETHTOOL_MSG_WOL_SET, wol),
	NLMSG_DESC(ETHTOOL_MSG_FEATURES_GET, features),
	NLMSG_DESC(ETHTOOL_MSG_FEATURES_SET, features),
	NLMSG_DESC(ETHTOOL_MSG_PRIVFLAGS_GET, privflags),
	NLMSG_DESC(ETHTOOL_MSG_PRIVFLAGS_SET, privflags),
	NLMSG_DESC(ETHTOOL_MSG_RINGS_GET, rings),
	NLMSG_DESC(ETHTOOL_MSG_RINGS_SET, rings),
	NLMSG_DESC(ETHTOOL_MSG_CHANNELS_GET, channels),
	NLMSG_DESC(ETHTOOL_MSG_CHANNELS_SET, channels),
	NLMSG_DESC(ETHTOOL_MSG_COALESCE_GET, coalesce),
	NLMSG_DESC(ETHTOOL_MSG_COALESCE_SET, coalesce),
	NLMSG_DESC(ETHTOOL_MSG_PAUSE_GET, pause),
	NLMSG_DESC(ETHTOOL_MSG_PAUSE_SET, pause),
	NLMSG_DESC(ETHTOOL_MSG_EEE_GET, eee),
	NLMSG_DESC(ETHTOOL_MSG_EEE_SET, eee),
	NLMSG_DESC(ETHTOOL_MSG_TSINFO_GET, tsinfo),
};

const unsigned int ethnl_umsg_n_desc = ARRAY_SIZE(ethnl_umsg_desc);

const struct pretty_nlmsg_desc ethnl_kmsg_desc[] = {
	NLMSG_DESC_INVALID(ETHTOOL_MSG_KERNEL_NONE),
	NLMSG_DESC(ETHTOOL_MSG_STRSET_GET_REPLY, strset),
	NLMSG_DESC(ETHTOOL_MSG_LINKINFO_GET_REPLY, linkinfo),
	NLMSG_DESC(ETHTOOL_MSG_LINKINFO_NTF, linkinfo),
	NLMSG_DESC(ETHTOOL_MSG_LINKMODES_GET_REPLY, linkmodes),
	NLMSG_DESC(ETHTOOL_MSG_LINKMODES_NTF, linkmodes),
	NLMSG_DESC(ETHTOOL_MSG_LINKSTATE_GET_REPLY, linkstate),
	NLMSG_DESC(ETHTOOL_MSG_DEBUG_GET_REPLY, debug),
	NLMSG_DESC(ETHTOOL_MSG_DEBUG_NTF, debug),
	NLMSG_DESC(ETHTOOL_MSG_WOL_GET_REPLY, wol),
	NLMSG_DESC(ETHTOOL_MSG_WOL_NTF, wol),
	NLMSG_DESC(ETHTOOL_MSG_FEATURES_GET_REPLY, features),
	NLMSG_DESC(ETHTOOL_MSG_FEATURES_SET_REPLY, features),
	NLMSG_DESC(ETHTOOL_MSG_FEATURES_NTF, features),
	NLMSG_DESC(ETHTOOL_MSG_PRIVFLAGS_GET_REPLY, privflags),
	NLMSG_DESC(ETHTOOL_MSG_PRIVFLAGS_NTF, privflags),
	NLMSG_DESC(ETHTOOL_MSG_RINGS_GET_REPLY, rings),
	NLMSG_DESC(ETHTOOL_MSG_RINGS_NTF, rings),
	NLMSG_DESC(ETHTOOL_MSG_CHANNELS_GET_REPLY, channels),
	NLMSG_DESC(ETHTOOL_MSG_CHANNELS_NTF, channels),
	NLMSG_DESC(ETHTOOL_MSG_COALESCE_GET_REPLY, coalesce),
	NLMSG_DESC(ETHTOOL_MSG_COALESCE_NTF, coalesce),
	NLMSG_DESC(ETHTOOL_MSG_PAUSE_GET_REPLY, pause),
	NLMSG_DESC(ETHTOOL_MSG_PAUSE_NTF, pause),
	NLMSG_DESC(ETHTOOL_MSG_EEE_GET_REPLY, eee),
	NLMSG_DESC(ETHTOOL_MSG_EEE_NTF, eee),
	NLMSG_DESC(ETHTOOL_MSG_TSINFO_GET_REPLY, tsinfo),
};

const unsigned int ethnl_kmsg_n_desc = ARRAY_SIZE(ethnl_kmsg_desc);
