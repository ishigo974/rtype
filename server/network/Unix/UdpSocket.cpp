//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include "UdpSocket.hpp"

UdpSocket::UdpSocket(short int port)
        : BaseSocket()
{
    if ((_socket = socket(AF_INET, SOCK_DGRAM, getprotobyname("UDP")
            ->p_proto)) == -1)
        throw std::runtime_error("socket failed");
    _port = port;
}

UdpSocket::~UdpSocket()
{
}

bool UdpSocket::bind() const
{
    struct sockaddr_in addr;

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(_port);

    return (::bind(_socket, reinterpret_cast<struct sockaddr *>(&addr),
                   sizeof(addr)) >= 0);
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
