#pragma once
#include "PacketHendler.h"
#include "PacketType.h"

namespace Server
{
struct PacketRegister
{
	static void Register(PacketHendler& h)
	{
		h.Register_Handler(PACKET_TYPE::POSITION, [](ClientSession& Sender, PACKET_HEADER* Header, std::unordered_map<SOCKET, ClientSession>& Session)
		{
			POSITION_PACKET* pkt = reinterpret_cast<POSITION_PACKET*>(Header);
			std::cout << "위치 패킷 수신" << std::endl;
			for(auto& var : Session)
			{
				if(var.first == Sender.socket)
					continue;
				send(var.second.socket, reinterpret_cast<const char*>(pkt), pkt->header.sSize, 0);
			}
		});

		h.Register_Handler(PACKET_TYPE::ROTATION, [](ClientSession& Sender, PACKET_HEADER* Header, std::unordered_map<SOCKET, ClientSession>& Session)
		{
			ROTATION_PACKET* pkt = reinterpret_cast<ROTATION_PACKET*>(Header);
			std::cout << "회전 패킷 수신" << std::endl;
			for(auto& var : Session)
			{
				if(var.first == Sender.socket)
					continue;
				send(var.second.socket, reinterpret_cast<const char*>(pkt), pkt->header.sSize, 0);
			}
		});

		h.Register_Handler(PACKET_TYPE::FIRE, [](ClientSession& Sender, PACKET_HEADER* Header, std::unordered_map<SOCKET, ClientSession>& Session)
		{
			FIRE_PACKET* pkt = reinterpret_cast<FIRE_PACKET*>(Header);
			std::cout << "공격 패킷 수신" << std::endl;
			for(auto& var : Session)
			{
				if(var.first == Sender.socket)
					continue;
				send(var.second.socket, reinterpret_cast<const char*>(pkt), pkt->header.sSize, 0);
			}
		});
	}
};

}