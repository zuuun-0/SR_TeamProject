#pragma once

namespace Server
{
enum class PACKET_TYPE : unsigned char
{
	POSITION,
	ROTATION,
	FIRE,
};

#pragma pack(push, 1)
struct PACKET_HEADER
{
	PACKET_TYPE ePacketType{};
	unsigned short sSize = 0;
};
#pragma pack(pop)
}