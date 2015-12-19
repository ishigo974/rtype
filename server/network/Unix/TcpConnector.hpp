//
// Created by Denis Le Borgne on 14/12/2015.
//

#ifndef RTYPE_SERVER_TCPCONNECTOR_HPP
#define RTYPE_SERVER_TCPCONNECTOR_HPP

#include "ITcpConnector.hpp"
#include "TcpSocket.hpp"

class TcpConnector : public TcpSocket, public ITcpConnector
{
public:
    TcpConnector(std::string const& addr, short int port);
    virtual ~TcpConnector();

public:
    virtual short int getPort() const;
    virtual std::string const& getAddr() const;

public:
    virtual std::string toString() const;

public:
    virtual void connect();

public:
    virtual rSocket getSocket() const;
};

#endif //RTYPE_SERVER_TCPCONNECTOR_HPP
