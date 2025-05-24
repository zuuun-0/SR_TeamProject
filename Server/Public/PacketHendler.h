#pragma once
#include "PacketType.h"

namespace Server
{
class PacketHendler
{
public:
	using HandlerFN = std::function<void(ClientSession& Sender, PACKET_HEADER* Header, std::unordered_map<SOCKET, ClientSession>& Session)>;

public:
	void Register_Handler(PACKET_TYPE Type, HandlerFN&& FN);
	void DispatchPacket(ClientSession& Sender, PACKET_HEADER* Header, std::unordered_map<SOCKET, ClientSession>& Session);

private:
	std::unordered_map<PACKET_TYPE, HandlerFN> m_Handlers;
};
}

