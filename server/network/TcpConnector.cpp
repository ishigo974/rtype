//
// Created by Denis Le Borgne on 06/12/2015.
//

#include <sys/socket.h>
#include <netdb.h>
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
    (void)buffer;
    return 0;
}

size_t TcpConnector::receive(Buffer& buffer, size_t len) const
{
    (void)buffer;
    (void)len;
    return 0;
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
    return false;
}
