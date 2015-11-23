//
// Created by Denis Le Borgne on 21/11/2015.
//

#include <cstring>
#include <netdb.h>
#include "TcpSocket.hpp"

TcpSocket::TcpSocket(std::string const& addr, short int port)
{
    _socket = socket(AF_INET, SOCK_DGRAM, getprotobyname("TCP")->p_proto);
    _port   = port;
    _addr   = addr;
}

TcpSocket::TcpSocket(int socket, std::string const& addr, short int port)
//TODO typedef
{
    _socket = socket;
    _port   = port;
    _addr   = addr;
}

ssize_t TcpSocket::send(const Buffer *buffer) const
{
    return (::send(_socket, buffer->data(), buffer->size(), MSG_DONTWAIT));
}

Buffer const *TcpSocket::recv() const
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

void TcpSocket::close() const
{
    ::close(_socket);
}

//TODO
bool TcpSocket::isReadable() const
{
    return (true);
}

//TODO
bool TcpSocket::isWritable() const
{
    return (true);
}

short int TcpSocket::getPort() const
{
    return (this->_port);
}

//TODO typedef
int TcpSocket::getSocket() const
{
    return (this->_socket);
}

std::string const& TcpSocket::getAddr() const
{
    return (this->_addr);
}

void TcpSocket::setPort(short int port)
{
    _port = port;
}

void TcpSocket::setAddr(const std::string& addr)
{
    _addr = addr;
}