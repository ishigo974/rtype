//
// Created by Denis Le Borgne on 23/11/2015.
//

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <sstream>
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
    if (listen(_socket, 5) == -1)
    {
        std::cerr << "Nothing to listen" << std::endl;
        //TODO throw exception
    }
}

TcpAcceptor::~TcpAcceptor()
{
    ::close(_socket);
}

ITcpSocket *TcpAcceptor::accept() const
{
    struct sockaddr_in client;
    int                socket; //TODO typedef
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
}

ssize_t TcpAcceptor::send(const Buffer *buffer) const
{
    return (::send(_socket, buffer->data(), buffer->size(), MSG_DONTWAIT));
}

Buffer const *TcpAcceptor::recv() const
{
    Buffer  *toRead = new Buffer;
    ssize_t ret;
    char    *buff;

    buff = new char[256];

    if ((ret = ::recv(_socket, buff, 256, MSG_DONTWAIT)) == -1)
        return (nullptr);
    toRead->setData(buff, (uint32_t) ret);
    std::memset(buff, 0, 256);
    while ((ret = ::recv(_socket, buff, 256, MSG_DONTWAIT)) != -1)
    {
        toRead->append(buff, (uint32_t) ret);
        std::memset(buff, 0, 256);
    }
    return (toRead);
}

void TcpAcceptor::close() const
{
    ::close(_socket);
}

short int TcpAcceptor::getPort() const
{
    return (this->_port);
}

//TODO typedef
int TcpAcceptor::getSocket() const
{
    return (this->_socket);
}

void TcpAcceptor::setPort(short int port)
{
    _port = port;
}

void TcpAcceptor::registerToMonitor(fd_set *fdSet, unsigned int *maxFd) const
{
    FD_SET(_socket, fdSet);
    if (*maxFd < _socket)
        *maxFd = _socket;
}

void TcpAcceptor::deleteFromMonitor(fd_set *fdSet) const
{
    FD_CLR(_socket, fdSet);
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
