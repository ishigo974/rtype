//
// Created by Denis Le Borgne on 21/11/2015.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else

#include <netdb.h>
#include <unistd.h>

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
    _port = port;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

size_t    UdpSocket::send(Buffer const& /*buffer*/) const
{
    return 0;
}

size_t    UdpSocket::receive(Buffer& /*buffer*/, size_t /*len*/) const
{
    return 0;
}

#else

size_t        UdpSocket::send(Buffer const& buffer) const
{
    ssize_t ret;

    if ((ret = ::send(_socket, buffer.data(), buffer.size(), 0))
        == -1)
    { ; //TODO throw
    }
    return (static_cast<size_t>(ret));
}

size_t        UdpSocket::receive(Buffer& buffer, size_t len) const
{
    ssize_t ret;
    char    *buff = new char[len];

    if ((ret = ::recv(_socket, buff, len, 0)) == -1)
        throw std::runtime_error("receive failed");
    buffer.setData(buff, static_cast<size_t>(ret));
    return static_cast<size_t>(ret);

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
