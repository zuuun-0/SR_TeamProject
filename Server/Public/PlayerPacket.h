#pragma once
#include "PacketType.h"

namespace Server
{
#pragma pack(push, 1)
typedef struct tagTransformPacket
{
	PacketHeader header;
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vRight;
	D3DXVECTOR3 vUp;
	D3DXVECTOR3 vLook;
}TRANSFORMPACKET;

struct FIREPACKET
{
	PacketHeader header;
	D3DVECTOR Pos;
};

#pragma pack(pop)
}
