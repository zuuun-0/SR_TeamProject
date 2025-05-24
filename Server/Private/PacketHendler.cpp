#include "PacketHendler.h"

void Server::PacketHendler::Register_Handler(PACKET_TYPE Type, HandlerFN&& FN)
{
	m_Handlers.emplace(Type, std::move(FN));
}

void Server::PacketHendler::DispatchPacket(ClientSession& Sender, PACKET_HEADER* Header, std::unordered_map<SOCKET, ClientSession>& Session)
{
	auto iter = m_Handlers.find(Header->ePacketType);
	if(iter == m_Handlers.end())
		assert(false && "존재 하지 않는 패킷 핸들러");

	iter->second(Sender, Header, Session);
}
