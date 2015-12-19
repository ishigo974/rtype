//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <stdexcept>
#include <iostream>
#include <sstream>
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"

TcpAcceptor::TcpAcceptor(short int port)
        : _port(port)
{
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
}

TcpAcceptor::~TcpAcceptor()
{
    close();
}

ITcpSocket *TcpAcceptor::accept() const
{
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
}

void TcpAcceptor::close()
{
    closesocket(_socket);
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