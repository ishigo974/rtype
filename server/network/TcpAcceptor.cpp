//
// Created by Denis Le Borgne on 23/11/2015.
//


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else

#include <arpa/inet.h>
#include <netdb.h>

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
    if (::bind(_socket, (const struct sockaddr *) (&server),
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
    struct sockaddr addr;
    int socklen;

    socklen = sizeof(addr);
    if ((socket = accept(_socket, &addr, &socklen)) == INVALID_SOCKET)
        return (nullptr);
    TcpSocket* ret - new TcpSocket(socket, (struct in_addr *)inet_ntoa(addr),
     _port);
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

size_t TcpAcceptor::send(const Buffer *buffer) const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    return 0;
#else
    return (::send(_socket, buffer->data(), buffer->size(), MSG_DONTWAIT));
#endif
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
Buffer const* TcpAcceptor::recv() const
{
    return nullptr;
}

#else

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

#endif

void TcpAcceptor::close() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    closesocket(_socket);
#else
    ::close(_socket);
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
