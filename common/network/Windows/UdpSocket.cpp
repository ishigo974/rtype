//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <cstring>
#include "SocketMonitor.hpp"
#include "UdpSocket.hpp"

int UdpSocket::defaultTimeout = 1;

UdpSocket::UdpSocket(short int port)
        : BaseSocket()
{
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        throw std::runtime_error("WSAStartup failed");
    if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
        throw std::runtime_error("Socket failed");
    _port        = port;
}

size_t    UdpSocket::sendTo(Buffer const& buffer, std::string const& addr) const
{
    struct sockaddr_in client;
    WSABUF             toSend;
    DWORD              SendBytes = 0;
    size_t             ret;
    std::vector<char>  buff(buffer.data(), buffer.data() + buffer.size());
    std::string        address(addr);

	toSend.len        = buffer.size();
    toSend.buf        = buff.data();
    client.sin_family = AF_INET;
	inet_pton(AF_INET, address.c_str(), &(client.sin_addr));
    client.sin_port = htons(_port);
	char               pd[16];
	inet_ntop(AF_INET, &(client.sin_addr), pd, INET_ADDRSTRLEN);

	if ((ret = sendto(_socket, buff.data(), buff.size(), 0,
		reinterpret_cast<SOCKADDR *>(&client), sizeof(client))) == SOCKET_ERROR)
	{
		std::cout << WSAGetLastError() << std::endl;
		throw std::runtime_error("WSASend failed");
	}
	return ret;
}

size_t    UdpSocket::receiveFrom(Buffer& buffer, size_t len, std::string& addr)
const
{
    WSABUF             wsabuf;
    DWORD              read_size  = 0;
    DWORD              flags      = 0;
    struct sockaddr_in client;
    int                clientSize = sizeof(client);
    char               address[16];

	if (setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char *>(&defaultTimeout), sizeof(defaultTimeout)) < 0) {
		perror("Error");
	}
    wsabuf.buf = new char[len];
    wsabuf.len = len;
    if (::WSARecvFrom(_socket, &wsabuf, 1, &read_size, &flags,
                      reinterpret_cast<SOCKADDR *>(&client), &clientSize,
                      nullptr, nullptr) == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAETIMEDOUT || WSAGetLastError() == WSAEINVAL)
            read_size = 0;
        else
        {
            delete wsabuf.buf;
            throw std::runtime_error("WSARecv failed");
        }
    }
	if (read_size > 0)
    {
        buffer.append(wsabuf.buf, read_size);
        inet_ntop(AF_INET, &(client.sin_addr), address, INET_ADDRSTRLEN);
        addr.assign(address);
    }
    delete wsabuf.buf;
    return (read_size);
}

bool UdpSocket::bind() const
{
    struct sockaddr_in server;

    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(_port);
    if (::bind(_socket, reinterpret_cast<struct sockaddr *>(&server),
               sizeof(server)) == SOCKET_ERROR)
        throw std::runtime_error("bind failed");
    return true;
}

short int UdpSocket::getPort() const
{
    return (this->_port);
}

rSocket UdpSocket::getSocket() const
{
    return (this->_socket);
}

void UdpSocket::setPort(short int port)
{
    _port = port;
}

void UdpSocket::setTimeoutSec(long)
{
}

void UdpSocket::setTimeoutUsec(long)
{
}

long UdpSocket::getTimeoutSec() const
{
	return 0;
}

long UdpSocket::getTimeoutUsec() const
{
	return 0;
}

std::string UdpSocket::toString() const
{
    std::string ss;

    ss += "UdpSocket {";
    ss += "\n\tSocket ";
    ss += this->_socket;
    ss += "\n\tPort ";
    ss += std::to_string(_port);
    ss += "\n}\n";

    return ss;
}

size_t UdpSocket::send(Buffer const& buffer) const
{
    return BaseSocket::send(buffer);
}

size_t UdpSocket::receive(Buffer& buffer, size_t len) const
{
    return BaseSocket::receive(buffer, len);
}

void UdpSocket::close() const
{
    BaseSocket::close();
}
