//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <cstring>
#include <iostream>
#include <sstream>
#include "TcpSocket.hpp"

TcpSocket::TcpSocket(std::string const& addr, short int port)
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::runtime_error("WSAStartup failed");
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        throw std::runtime_error("LOBYTE / HIBYTE failed");
    }
    if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        throw std::runtime_error("Socket failed");
    _port = port;
    _addr = addr;
}

TcpSocket::TcpSocket(rSocket socket, std::string const& addr, short int port)
{
    _socket = socket;
    _port   = port;
    _addr   = addr;
}

short int TcpSocket::getPort() const
{
    return (this->_port);
}

rSocket TcpSocket::getSocket() const
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

    ss  << "TcpSocket {"
    << "\n\tAddress " << this->_addr
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
}

TcpSocket::~TcpSocket()
{
    this->close();
}

size_t TcpSocket::send(Buffer const& buffer) const
{
    return BaseSocket::send(buffer);
}

size_t TcpSocket::receive(Buffer& buffer, size_t len) const
{
    return BaseSocket::receive(buffer, len);
}

void TcpSocket::close() const
{
    BaseSocket::close();
}
