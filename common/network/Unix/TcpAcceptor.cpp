//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"

TcpAcceptor::TcpAcceptor(short int port)
        : _port(port)
{
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
}

TcpAcceptor::~TcpAcceptor()
{
    close();
}

ITcpSocket *TcpAcceptor::accept() const
{
    struct sockaddr_in client;
    rSocket            socket;
    unsigned int       struct_len;

    struct_len  = sizeof(client);
    if ((socket = ::accept(_socket, reinterpret_cast<struct sockaddr *>(&client),
                           &struct_len)) < 0)
        throw std::runtime_error("can't accept");
    TcpSocket *ret = new TcpSocket(socket, inet_ntoa(client.sin_addr), _port);
    return (ret);
}

void TcpAcceptor::close()
{
    ::close(this->_socket);
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
    std::string ss;

    ss += "TcpAcceptor {";
    ss += "\n\tSocket ";
    ss += this->_socket;
    ss += "\n\tPort ";
    ss += this->_port;
    ss += "\n}\n";
    return ss;
}
