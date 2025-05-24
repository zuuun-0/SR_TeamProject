#pragma once

namespace Server
{
struct ClientSession
{
	SOCKET socket;
	std::deque<char> recvBuf;
};
}