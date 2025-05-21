#pragma once

namespace Server
{
#pragma pack(push, 1)
enum class PACKETTYPE : unsigned char
{
	TRANFORM,
	FIRE,
};

struct PacketHeader
{
	PACKETTYPE ePacketType;
	unsigned short sSize;
};
#pragma pack(pop)
}