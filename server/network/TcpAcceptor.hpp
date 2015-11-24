//
// Created by Denis Le Borgne on 19/11/2015.
//

#ifndef RTYPE_TCPACCEPTOR_HPP
#define RTYPE_TCPACCEPTOR_HPP

#include "ITcpAcceptor.hpp"

class TcpAcceptor : public ITcpAcceptor
{
public:
    TcpAcceptor(short int port);
    virtual ~TcpAcceptor();

public:
    virtual ITcpSocket *accept() const;

public:
    virtual ssize_t      send(Buffer const *buffer) const;
    virtual Buffer const *recv() const;
    virtual void         close() const;
    virtual bool         isReadable(fd_set *fdSet) const;
    virtual bool         isWritable(fd_set *fdSet) const;

public:
    virtual void registerToMonitor(fd_set *fdSet, unsigned int *maxFd) const;
    virtual void deleteFromMonitor(fd_set *fdSet) const;

public:
    int       getSocket() const; //DO TO TYPEDEF FOR SOCKET
    short int getPort() const;

    void setPort(short int port);

private:
    TcpAcceptor(TcpAcceptor const& acceptor) = delete;
    TcpAcceptor& operator=(TcpAcceptor const& acceptor) = delete;

private:
    short int _port;
    int       _socket; //TODO typedef
};

#endif //RTYPE_TCPACCEPTOR_HPP
