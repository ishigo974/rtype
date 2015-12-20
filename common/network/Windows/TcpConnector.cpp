//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <sstream>
#include "TcpConnector.hpp"

TcpConnector::TcpConnector(std::string const& addr, short int port)
        : TcpSocket(addr, port)
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::runtime_error("WSAStartup failed");
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
        throw std::runtime_error("LOBYTE / HIBYTE failed");
    if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        throw std::runtime_error("Socket failed");
}

TcpConnector::~TcpConnector()
{
    close();
}

short int TcpConnector::getPort() const
{
    return _port;
}

std::string const& TcpConnector::getAddr() const
{
    return _addr;
}

void TcpConnector::connect()
{
    struct sockaddr_in sin;

    inet_pton(AF_INET, _addr.c_str(), &sin.sin_addr);
    sin.sin_port   = htons(_port);
    sin.sin_family = AF_INET;

    if (WSAConnect(_socket, reinterpret_cast<struct sockaddr *>(&sin),
                   sizeof(SOCKADDR), nullptr, nullptr, nullptr, nullptr)
        == SOCKET_ERROR)
        throw std::runtime_error("Can't connect to server");
}

rSocket TcpConnector::getSocket() const
{
    return _socket;
}

std::string TcpConnector::toString() const
{
    std::string ss;

    ss += "TcpConnector {";
    ss += "\n\tSocket ";
    ss += this->_socket;
    ss += "\n\tPort ";
    ss += this->_port;
    ss += "\n}\n";

    return ss;
}
