//using namespace Server;
//
//
//int FindClinetIndex(sockaddr_in& FROM);
//
//sockaddr_in clients[2]{};
//bool clientRegister[2]{};
//
//int main()
//{
//	WSADATA data{};
//	int result = WSAStartup(MAKEWORD(2, 2), &data);
//	if(result != 0)
//	{
//		assert(false);
//	}
//
//	SOCKET serverSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//	if(serverSock == SOCKET_ERROR)
//	{
//		WSACleanup();
//		assert(false);
//	}
//
//	sockaddr_in addr{};
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(1530);
//	addr.sin_addr.s_addr = INADDR_ANY;
//
//	if(bind(serverSock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
//	{
//		closesocket(serverSock);
//		WSACleanup();
//		assert(false);
//	}
//	std::cout << "UDP 서버 시작됨\n";
//
//	while(true)
//	{
//		sockaddr_in fromAddr{};
//		int fromLen = sizeof(fromAddr);
//		char buffer[1024]{};
//
//		int len = recvfrom(serverSock, buffer, sizeof(buffer), 0, (sockaddr*)&fromAddr, &fromLen);
//		if(len <= 0) continue;
//
//		int fromIndex = FindClinetIndex(fromAddr);
//		int toIndex = (fromIndex + 1) % 2;
//
//		if(fromIndex == -1 || !clientRegister[toIndex])
//			continue;
//
//
//		if(len < sizeof(PacketHeader)) continue;
//
//		auto* header = reinterpret_cast<PacketHeader*>(buffer);
//		switch(header->ePacketType)
//		{
//			case PACKETTYPE::TRANFORM:
//			std::cout << "트랜스폼 정보 수신" << '\r' << std::flush;
//			break;
//			case PACKETTYPE::FIRE:
//			std::cout << "총알 정보 수신" << '\r' << std::flush;
//			default:
//			std::cout << "알 수 없는 패킷 타입" << '\r' << std::flush;
//			break;
//		}
//
//
//
//
//
//		sendto(serverSock, buffer, len, 0, (sockaddr*)&clients[toIndex], sizeof(sockaddr_in));
//	}
//	closesocket(serverSock);
//	WSACleanup();
//	return 0;
//}
//
//int FindClinetIndex(sockaddr_in& FROM)
//{
//	for(int i = 0; i < 2; ++i)
//	{
//		if(clientRegister[i] &&
//		   clients[i].sin_addr.s_addr == FROM.sin_addr.s_addr &&
//		   clients[i].sin_port == FROM.sin_port)
//		{
//			return i;
//		}
//	}
//
//	for(int i = 0; i < 2; ++i)
//	{
//		if(!clientRegister[i])
//		{
//			clients[i] = FROM;
//			clientRegister[i] = true;
//			std::cout << "클라이언트 " << i << "등록됨" << std::endl;
//			return i;
//		}
//	}
//	return -1;
//}


std::unordered_map<SOCKET, ClientSession> g_Session;
PacketHendler g_Handler;

int main()
{
	WSAData	data{};
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if(result != 0)
	{
		WSACleanup();
		return 1;
	}

	SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSock == INVALID_SOCKET)
	{
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1530);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(serverSock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR)
	{
		closesocket(serverSock);
		WSACleanup();
		return 1;
	}

	if(listen(serverSock, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(serverSock);
		WSACleanup();
		return 1;
	}
	PacketRegister::Register(g_Handler);

	std::cout << "서버 대기 중...." << std::endl;

	FD_SET readSet{};
	FD_ZERO(&readSet);
	FD_SET(serverSock, &readSet);

	while(true)
	{
		FD_SET tempSet = readSet;
		int activity = select(0, &tempSet, nullptr, nullptr, nullptr);

		for(u_int i = 0; i < readSet.fd_count; ++i)
		{
			SOCKET clientSock = readSet.fd_array[i];

			if(FD_ISSET(clientSock, &tempSet))
			{
				if(clientSock == serverSock)
				{
					SOCKET newClinet = accept(serverSock, nullptr, nullptr);
					if(newClinet != INVALID_SOCKET)
					{
						FD_SET(newClinet, &readSet);
						g_Session.emplace(newClinet, ClientSession{ newClinet });
						std::cout << "클라이언트 접속됨 << (소켓 " << newClinet << ")" << std::endl;
					}
					continue;
				}

				char buffer[512]{};
				int recvLen = recv(clientSock, buffer, sizeof(buffer), 0);
				if(recvLen <= 0)
				{
					std::cout << "클라이언트 연결 종료됨 (소켓 " << clientSock << ")" << std::endl;
					closesocket(clientSock);
					FD_CLR(clientSock, &readSet);
					g_Session.erase(clientSock);
					--i;
					continue;
				}

				auto& recvBuffer = g_Session[clientSock].recvBuf;
				recvBuffer.insert(recvBuffer.end(), buffer, buffer + recvLen);

				while(true)
				{
					if(recvBuffer.size() < sizeof(PACKET_HEADER)) break;

					PACKET_HEADER header{};
					std::copy_n(recvBuffer.begin(), sizeof(PACKET_HEADER), reinterpret_cast<char*>(&header));
					if(recvBuffer.size() < header.sSize) break;

					std::vector<char> onePacket(recvBuffer.begin(), recvBuffer.begin() + header.sSize);

					PACKET_HEADER* realHeader = reinterpret_cast<PACKET_HEADER*>(onePacket.data());

					g_Handler.DispatchPacket(g_Session[clientSock], realHeader, g_Session);
					recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + header.sSize);
				}
			}
		}
	}
}
