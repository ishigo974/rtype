//
// Created by Denis Le Borgne on 23/11/2015.
//

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"

TcpAcceptor::TcpAcceptor(short int port)
{
    struct sockaddr_in server;

    _port = port;
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(_port);

    if (::bind(_socket, reinterpret_cast<struct sockaddr *>(&server),
               sizeof(server)) < 0)
        //TODO throw exception;
        ;

}

ITcpSocket const *TcpAcceptor::accept() const
{
    struct sockaddr_in client;
    int                socket; //TODO typedef
    unsigned int       struct_len;

    listen(_socket, 2);
    struct_len  = sizeof(client);
    if ((socket = ::accept(_socket,
                           reinterpret_cast<struct sockaddr *>(&client),
                           &struct_len)) < 0)
    {
        std::cerr << "Can't accept on socket." << std::endl;
        return (nullptr);
    }

    TcpSocket *ret = new TcpSocket(std::string(inet_ntoa(client.sin_addr)),
                                   socket);
    return (ret);
}