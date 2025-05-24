#pragma once

namespace std
{
template<>
struct hash<Server::PACKET_TYPE>
{
	size_t operator()(const Server::PACKET_TYPE& type) const noexcept
	{
		return static_cast<size_t>(type);
	}
};
}