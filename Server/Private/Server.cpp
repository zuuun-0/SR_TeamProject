using namespace Server;


int FindClinetIndex(sockaddr_in& FROM);

sockaddr_in clients[2]{};
bool clientRegister[2]{};

int main()
{
	WSADATA data{};
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if(result != 0)
	{
		assert(false);
	}

	SOCKET serverSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(serverSock == SOCKET_ERROR)
	{
		WSACleanup();
		assert(false);
	}

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1530);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(serverSock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		closesocket(serverSock);
		WSACleanup();
		assert(false);
	}
	std::cout << "UDP 서버 시작됨\n";

	while(true)
	{
		sockaddr_in fromAddr{};
		int fromLen = sizeof(fromAddr);
		char buffer[1024]{};

		int len = recvfrom(serverSock, buffer, sizeof(buffer), 0, (sockaddr*)&fromAddr, &fromLen);
		if(len <= 0) continue;

		int fromIndex = FindClinetIndex(fromAddr);
		int toIndex = (fromIndex + 1) % 2;

		if(fromIndex == -1 || !clientRegister[toIndex])
			continue;


		if(len < sizeof(PACKET_HEADER)) continue;

		auto* header = reinterpret_cast<PACKET_HEADER*>(buffer);
		switch(header->ePacketType)
		{
			if(len >= sizeof(POSITION_PACKET))
			{
			case PACKET_TYPE::POSITION:
			std::cout << "위치 정보 수신" << '\r' << std::flush;
			}
			break;
			if(len >= sizeof(ROTATION_PACKET))
			{
			case PACKET_TYPE::ROTATION:
			std::cout << "회전 정보 수신" << '\r' << std::flush;
			}
			break;
			if(len >= sizeof(FIRE_PACKET))
			{
			case PACKET_TYPE::FIRE:
			std::cout << "총알 정보 수신" << '\r' << std::flush;
			}
			break;
			default:
			std::cout << "알 수 없는 패킷 타입" << '\r' << std::flush;
			break;
		}


		sendto(serverSock, buffer, len, 0, (sockaddr*)&clients[toIndex], sizeof(sockaddr_in));
	}
	closesocket(serverSock);
	WSACleanup();
	return 0;
}

int FindClinetIndex(sockaddr_in& FROM)
{
	for(int i = 0; i < 2; ++i)
	{
		if(clientRegister[i] &&
		   clients[i].sin_addr.s_addr == FROM.sin_addr.s_addr &&
		   clients[i].sin_port == FROM.sin_port)
		{
			return i;
		}
	}

	for(int i = 0; i < 2; ++i)
	{
		if(!clientRegister[i])
		{
			clients[i] = FROM;
			clientRegister[i] = true;
			std::cout << "클라이언트 " << i << "등록됨" << std::endl;
			return i;
		}
	}
	return -1;
}
