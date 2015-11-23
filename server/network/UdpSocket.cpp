//
// Created by Denis Le Borgne on 21/11/2015.
//

#include <cstring>
#include <netdb.h>
#include "UdpSocket.hpp"

UdpSocket::UdpSocket(short int port)
{

    _socket = socket(AF_INET, SOCK_DGRAM, getprotobyname("UDP")->p_proto);
    _port   = port;
}

ssize_t UdpSocket::send(const Buffer *buffer) const
{
    return (::send(_socket, buffer->data(), buffer->size(), MSG_DONTWAIT));
}

Buffer const *UdpSocket::recv() const
{
    Buffer  *toRead = new Buffer;
    ssize_t ret;
    char    *buff   = new char[256];

    if ((ret = ::recv(_socket, buff, 256, MSG_DONTWAIT)) == -1)
        return (nullptr);
    toRead->setData(buff, (uint32_t) ret);
    std::memset(buff, 0, 256);
    while ((ret = ::recv(_socket, buff, 256, MSG_DONTWAIT)) != -1)
    {
        toRead->append(buff, (uint32_t) ret);
        std::memset(buff, 0, 256);
    }
    return (toRead);
}

void UdpSocket::close() const
{
    ::close(_socket);
}

//TODO
bool UdpSocket::isReadable() const
{
    return (true);
}

//TODO
bool UdpSocket::isWritable() const
{
    return (true);
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

//TODO typedef
int UdpSocket::getSocket() const
{
    return (this->_socket);
}

void UdpSocket::setPort(short int port)
{
    _port = port;
}