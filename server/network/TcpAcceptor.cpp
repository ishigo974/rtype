//
// Created by Denis Le Borgne on 23/11/2015.
//


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#else

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#endif

#include <stdexcept>
#include <iostream>
#include <sstream>
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"

TcpAcceptor::TcpAcceptor(short int port)
        : _port(port)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSADATA wsaData;
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(_port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::runtime_error("WSAStartup failed");
    if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
        throw std::runtime_error("Socket failed");
    if (::bind(_socket, reinterpret_cast<SOCKADDR *>(&server), sizeof(server)) == SOCKET_ERROR)
        throw std::runtime_error("can't bind port " + std::to_string(port));
    if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
        throw std::runtime_error("listen failed");
#else
    struct sockaddr_in server;

    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(_port);

    if ((_socket = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")
            ->p_proto)) == -1)
        throw std::runtime_error("socket failed");
    if (::bind(_socket, reinterpret_cast<const struct sockaddr *>(&server),
               sizeof(server)) == -1)
        throw std::runtime_error("can't bind port " + std::to_string(port));
    if (::listen(_socket, SOMAXCONN) == -1)
        throw std::runtime_error("listen failed");
#endif
}

TcpAcceptor::~TcpAcceptor()
{
    close();
}

ITcpSocket *TcpAcceptor::accept() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    rSocket socket;
    struct sockaddr_in addr;
    int socklen;
    char *address = new char[16];

    socklen = sizeof(addr);
    if ((socket = WSAAccept(_socket, reinterpret_cast<sockaddr*>(&addr), &socklen, nullptr, NULL)) == INVALID_SOCKET)
           throw std::runtime_error("can't accept");
    inet_ntop(AF_INET, &(addr.sin_addr), address, INET_ADDRSTRLEN);
    auto* ret = new TcpSocket(socket, address, _port);
    return ret;
#else
    struct sockaddr_in client;
    rSocket            socket;
    unsigned int       struct_len;

    struct_len  = sizeof(client);
    if ((socket = ::accept(_socket,
                           reinterpret_cast<struct sockaddr *>(&client),
                           &struct_len)) < 0)
        throw std::runtime_error("can't accept");
    TcpSocket *ret = new TcpSocket(socket, inet_ntoa(client.sin_addr), _port);
    return (ret);
#endif
}

void TcpAcceptor::close()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    closesocket(_socket);
#else
    ::close(this->_socket);
#endif
}

short int TcpAcceptor::getPort() const
{
    return (this->_port);
}

rSocket TcpAcceptor::getSocket() const
{
    return (this->_socket);
}

void TcpAcceptor::setPort(short int port)
{
    _port = port;
}

std::string TcpAcceptor::toString() const
{
    std::ostringstream ss;

    ss << "TcpAcceptor {"
    << "\n\tSocket " << this->_socket
    << "\n\tPort " << this->_port
    << "\n}" << std::endl;

    return ss.str();
}
