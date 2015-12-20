//
// Created by Denis Le Borgne on 14/12/2015.
//

#ifndef RTYPE_SERVER_TCPACCEPTOR_HPP
#define RTYPE_SERVER_TCPACCEPTOR_HPP

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
    virtual ITcpSocket *accept() const;

public:
    virtual std::string toString() const;

public:
    virtual rSocket   getSocket() const;

public:
    short int getPort() const;
    void setPort(short int port);
    void close();

private:
    short int _port;
    rSocket   _socket;
};

#endif //RTYPE_SERVER_TCPACCEPTOR_HPP
