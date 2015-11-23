//
// Created by Denis Le Borgne on 23/11/2015.
//

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"

TcpAcceptor::TcpAcceptor(short int port)
{
    struct sockaddr_in server;

    _port = port;
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(_port);

    if ((_socket = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")
            ->p_proto)) == -1)
        //TODO throw exception
        std::cerr << "Can' listen" << std::endl;
    if (::bind(_socket, (const struct sockaddr *) (&server),
               sizeof(server)) == -1)
        //TODO throw exception;
        std::cout << "Can't bind port" << std::endl;

}

TcpAcceptor::~TcpAcceptor()
{
    close(_socket);
}

ITcpSocket const *TcpAcceptor::accept() const
{
    struct sockaddr_in client;
    int                socket; //TODO typedef
    unsigned int       struct_len;

    if (listen(_socket, 5) == -1)
    {
        std::cerr << "Nothing to listen" << std::endl;
        return (nullptr);
    }
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
}