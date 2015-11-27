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

private:
    TcpAcceptor(TcpAcceptor const& acceptor) = delete;
    TcpAcceptor& operator=(TcpAcceptor const& acceptor) = delete;

public:
    virtual ITcpSocket*   accept() const;

public:
    virtual std::string   toString() const;

public:
    int           getSocket() const; //DO TO TYPEDEF FOR SOCKET
    short int     getPort() const;

public:
    void          setPort(short int port);

private:
    short int     _port;
    int           _socket; //TODO typedef
};

#endif //RTYPE_TCPACCEPTOR_HPP
