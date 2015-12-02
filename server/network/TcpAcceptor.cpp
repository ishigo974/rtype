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

#include <iostream>
#include <sstream>
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"

TcpAcceptor::TcpAcceptor(short int port)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    (void)port;
#else
    struct sockaddr_in server;

    _port = port;
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(_port);

    if ((_socket = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")
            ->p_proto)) == -1)
        //TODO throw exception
        std::cerr << "Can' listen" << std::endl;
    if (::bind(_socket, reinterpret_cast<const struct sockaddr *>(&server),
               sizeof(server)) == -1)
        //TODO throw exception;
        std::cout << "Can't bind port" << std::endl;
    if (listen(_socket, 5) == -1)
    {
        std::cerr << "Nothing to listen" << std::endl;
        //TODO throw exception
    }
#endif
}

TcpAcceptor::~TcpAcceptor()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
    ::close(_socket);
#endif
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
        return (nullptr);
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
    {
        std::cerr << "Can't accept on socket." << std::endl;
        return (nullptr);
    }
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
