//
// Created by Denis Le Borgne on 21/11/2015.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else

#include <netdb.h>
#include <unistd.h>

#endif

#include <cstring>
#include <iostream>
#include <sstream>
#include "TcpSocket.hpp"

TcpSocket::TcpSocket(std::string const& addr, short int port)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2);, &wsaData) != 0)
    { ; //TODO throw
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup();
        //TODO throw
    }
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    _socket = socket(AF_INET, SOCK_DGRAM, getprotobyname("TCP")->p_proto);
#endif
    _port = port;
    _addr = addr;
}

TcpSocket::TcpSocket(rSocket socket, std::string const& addr, short int port)
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

size_t        TcpSocket::send(Buffer const& buffer) const
{
    ssize_t ret;

    if ((ret = ::send(_socket, buffer.data(), buffer.size(), MSG_DONTWAIT))
        == -1)
        throw std::runtime_error("send failed");
    return (ret);
}

#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
Buffer const* TcpSocket::recv() const
{
    return nullptr;
}

#else

size_t        TcpSocket::receive(Buffer& buffer, size_t len) const
{
    ssize_t ret;
    char *buff = new char[len];

    if ((ret = ::recv(_socket, buff, len, MSG_DONTWAIT)) == -1)
        throw std::runtime_error("receive failed");
    buffer.setData(buff, ret);
    return ret;
}

#endif

void TcpSocket::close() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    closesocket(_socket);
#else
    ::close(_socket);
#endif
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

    ss << "TcpSocket {"
    << "\n\tAddress " << this->_addr
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
}

TcpSocket::~TcpSocket()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSACleanup();
#endif
    this->close();
}
