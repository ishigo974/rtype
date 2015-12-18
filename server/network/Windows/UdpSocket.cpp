//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <cstring>
#include <iostream>
#include <sstream>
#include "SocketMonitor.hpp"
#include "UdpSocket.hpp"

const int UdpSocket::defaultTimeout = 500;

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
    DWORD              SendBytes;
    size_t             ret;
    std::vector<char>  buff(buffer.data(), buffer.data() + buffer.size());
    std::vector<char>  address(buffer.data(), buffer.data() + buffer.size());

    toSend.len        = buffer.size();
    toSend.buf        = buff.data();
    client.sin_family = AF_INET;
    client.sin_addr.s_addr =
            inet_pton(AF_INET, address.data(), &client.sin_addr);
    client.sin_port = _port;

    if ((ret = WSASendTo(_socket, &toSend, 1, &SendBytes, 0,
                         reinterpret_cast<SOCKADDR *>(&client), sizeof(client),
                         nullptr, nullptr)) == SOCKET_ERROR)
        throw std::runtime_error("WSASend failed");
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
    char               *address   = new char[16];
    int                timeout;

    timeout = UdpSocket::defaultTimeout;

    if (setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO,
                   reinterpret_cast<char *>(&timeout), sizeof(timeout))
        == SOCKET_ERROR)
        throw std::runtime_error("SetSockOpt failed");
    wsabuf.buf = new char[len];
    wsabuf.len = len;
    if (::WSARecvFrom(_socket, &wsabuf, 1, &read_size, &flags,
                      reinterpret_cast<SOCKADDR *>(&client), &clientSize,
                      nullptr, nullptr) == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAETIMEDOUT)
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
        delete wsabuf.buf;
        inet_ntop(AF_INET, &(client.sin_addr), address, INET_ADDRSTRLEN);
        addr.assign(address);
    }
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

std::string UdpSocket::toString() const
{
    std::ostringstream ss;

    ss << "UdpSocket {"
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
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
