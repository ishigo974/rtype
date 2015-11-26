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
#include "UdpSocket.hpp"

UdpSocket::UdpSocket(short int port)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
    _socket = socket(AF_INET, SOCK_DGRAM, getprotobyname("UDP")->p_proto);
#endif
	_port   = port;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
size_t UdpSocket::send(Buffer const* buffer) const
{
	return 0;
}

Buffer const* UdpSocket::recv() const
{
	return nullptr;
}

#else
size_t UdpSocket::send(const Buffer *buffer) const
{
    ssize_t ret;

    if ((ret = ::send(_socket, buffer->data(), buffer->size(), MSG_DONTWAIT))
        == -1)
        ; //TODO throw
    return (static_cast<size_t>(ret));
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
#endif

void UdpSocket::close() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
    ::close(_socket);
#endif
}

bool UdpSocket::bind() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	return true;
#else
    struct sockaddr_in addr;

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(_port);

    return (::bind(_socket, reinterpret_cast<struct sockaddr *>(&addr),
                   sizeof(addr)) >= 0);
#endif
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

std::string UdpSocket::toString() const
{
    std::ostringstream ss;

    ss << "UdpSocket {"
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
}