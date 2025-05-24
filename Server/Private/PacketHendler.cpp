#include "PacketHendler.h"

void Server::PacketHendler::Register_Handler(PACKET_TYPE Type, HandlerFN&& FN)
{
	m_Handlers.emplace(Type, std::move(FN));
}

void Server::PacketHendler::DispatchPacket(ClientSession& Sender, PACKET_HEADER* Header, std::unordered_map<SOCKET, ClientSession>& Session)
{
	auto iter = m_Handlers.find(Header->ePacketType);
	if(iter == m_Handlers.end())
		assert(false && "���� ���� �ʴ� ��Ŷ �ڵ鷯");

	iter->second(Sender, Header, Session);
}
