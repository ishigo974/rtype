//
// Created by Denis Le Borgne on 06/12/2015.
//

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "TcpConnector.hpp"

TcpConnector::TcpConnector(std::string const& addr, short int port)
        : _addr(addr), _port(port)
{
    _socket = ::socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
}

TcpConnector::~TcpConnector()
{
    ::close(_socket);
}

void TcpConnector::close() const
{
    ::close(_socket);
}

size_t TcpConnector::send(Buffer const& buffer) const
{
    ssize_t ret;

    if ((ret = ::send(_socket, buffer.data(), buffer.size(), 0)) < 0)
        throw std::runtime_error("send failed");
    return static_cast<size_t >(ret);
}

size_t TcpConnector::receive(Buffer& buffer, size_t len) const
{
    ssize_t ret;
    char    *buff = new char[len];

    if ((ret = ::recv(_socket, buff, len, 0)) == -1)
        throw std::runtime_error("receive failed");
    buffer.setData(buff, static_cast<size_t>(ret));
    return static_cast<size_t>(ret);
}

short int TcpConnector::getPort() const
{
    return _port;
}

std::string const& TcpConnector::getAddr() const
{
    return _addr;
}

bool TcpConnector::connect()
{
    struct sockaddr_in sin;

    sin.sin_addr.s_addr = inet_addr(_addr.c_str());
    sin.sin_port        = htons(_port);
    sin.sin_family      = AF_INET;
    return (::connect(_socket, reinterpret_cast<struct sockaddr *>(&sin),
                      sizeof(sin)) >= 0);
}
