//
// Created by Denis Le Borgne on 06/12/2015.
//

#ifndef RTYPE_SERVER_TCPCONNECTOR_HPP
#define RTYPE_SERVER_TCPCONNECTOR_HPP

#include "ITcpConnector.hpp"

class TcpConnector : public ITcpConnector
{
public:
    TcpConnector(std::string const& addr, short int port);
    virtual ~TcpConnector();

public:
    virtual void   close() const;
    virtual size_t send(Buffer const& buffer) const;
    virtual size_t receive(Buffer& buffer, size_t len) const;

public:
    virtual short int getPort() const;
    virtual std::string const& getAddr() const;

public:
    virtual std::string toString() const;

public:
    virtual bool connect();

public:
    virtual rSocket getSocket() const;

private:
    rSocket     _socket;
    std::string _addr;
    short int   _port;
};


#endif //RTYPE_SERVER_TCPCONNECTOR_HPP
