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
#include "TcpSocket.hpp"

TcpSocket::TcpSocket(std::string const& addr, short int port)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::runtime_error("WSAStartup failed");
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        throw std::runtime_error("LOBYTE / HIBYTE failed");
    }
    if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        throw std::runtime_error("Socket failed");
#else
    _socket = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
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
size_t TcpSocket::send(Buffer const& buffer) const
{
    WSABUF toSend;
    DWORD SendBytes;
    size_t ret;
    std::vector<char> str(buffer.data(), buffer.data() + buffer.size());

    toSend.len = buffer.size();
    toSend.buf = str.data();
    if ((ret = WSASend(_socket, &toSend, 1, &SendBytes, 0, nullptr, nullptr)) == SOCKET_ERROR)
        throw std::runtime_error("WSASend failed");
    return ret;
}

#else

size_t        TcpSocket::send(Buffer const& buffer) const
{
    ssize_t ret;

    if ((ret = ::send(_socket, buffer.data(), buffer.size(), 0))
        == -1)
        throw std::runtime_error("send failed");
    return (static_cast<size_t>(ret));
}

#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
size_t        TcpSocket::receive(Buffer& buffer, size_t len) const
{
    WSABUF wsabuf;
    DWORD read_size = 0;
    DWORD flags = 0;


    wsabuf.buf = new char[len];
    wsabuf.len = len;
    if (::WSARecv(_socket, &wsabuf, 1, &read_size, &flags, nullptr, nullptr)
                  == SOCKET_ERROR)
          {
            delete wsabuf.buf;
            return 0;
          }
        buffer.append(wsabuf.buf, read_size);
        delete wsabuf.buf;
        return (read_size);
}

#else

size_t          TcpSocket::receive(Buffer& buffer, size_t len) const
{
    ssize_t ret;
    char    *buff = new char[len];

    if ((ret = ::recv(_socket, buff, len, 0)) == -1)
        throw std::runtime_error("receive failed");
    buffer.setData(buff, static_cast<size_t>(ret));
    delete[] buff;
    return static_cast<size_t>(ret);
}

#endif

void TcpSocket::close() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    std::cout << "___>" << (int)_socket << std::endl;
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
    this->close();
}
