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
    virtual ~TcpAcceptor() {}

public:
    virtual ITcpSocket const* accept() const;

private:
    TcpAcceptor(TcpAcceptor const& acceptor) = delete;
    TcpAcceptor& operator=(TcpAcceptor const& acceptor) = delete;

private:
    short int _port;
    int _socket; //TODO
};

#endif //RTYPE_TCPACCEPTOR_HPP
