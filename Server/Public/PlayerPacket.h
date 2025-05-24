#pragma once
#include "PacketType.h"

namespace Server
{
#pragma pack(push, 1)
typedef struct tagPositionPacket
{
	PACKET_HEADER header;
	D3DXVECTOR3 vPosition;

}POSITION_PACKET;

typedef	struct tagRotationPacket
{
	PACKET_HEADER header;
	D3DXVECTOR3 vRight;
	D3DXVECTOR3 vUp;
	D3DXVECTOR3 vLook;
}ROTATION_PACKET;

struct FIRE_PACKET
{
	PACKET_HEADER header;
	D3DVECTOR Pos;
};

#pragma pack(pop)
}
