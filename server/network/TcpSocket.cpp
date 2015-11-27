//
// Created by Denis Le Borgne on 21/11/2015.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
#include <netdb.h>
#endif
#include <cstring>
#include <iostream>
#include <sstream>
#include "TcpSocket.hpp"

TcpSocket::TcpSocket(std::string const& addr, short int port)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
	_socket = socket(AF_INET, SOCK_DGRAM, getprotobyname("TCP")->p_proto);
#endif
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

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
size_t TcpSocket::send(Buffer const* buffer) const
{
	return 0;
}

#else
size_t TcpSocket::send(const Buffer *buffer) const
{
    return (::send(_socket, buffer->data(), buffer->size(), MSG_DONTWAIT));
}
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
Buffer const* TcpSocket::recv() const
{
	return nullptr;
}

#else
Buffer const *TcpSocket::recv() const
{
    Buffer  *toRead = new Buffer;
    size_t ret;
    char    *buff;

    buff = new char[256];

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
#endif

void TcpSocket::close() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
    ::close(_socket);
#endif
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

std::string TcpSocket::toString() const
{
    std::ostringstream ss;

    ss << "TcpSocket {"
    << "\n\tAddresse " << this->_addr
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
}

TcpSocket::~TcpSocket()
{
    this->close();
}
