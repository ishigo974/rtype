//
// Created by Denis Le Borgne on 21/11/2015.
//

#ifndef RTYPE_TCPSOCKET_HPP
#define RTYPE_TCPSOCKET_HPP

# include "Buffer.hpp"
# include "ITcpSocket.hpp"

class TcpSocket : public ITcpSocket
{
public:
    TcpSocket(std::string const& addr, short int port);
    TcpSocket(rSocket socket, std::string const& addr,
              short int port);
    virtual ~TcpSocket();

public:
    virtual size_t        send(Buffer const& buffer) const;
    virtual size_t        receive(Buffer& buffer, size_t len) const;
    virtual void          close() const;

public:
    virtual std::string   toString() const;

public:
    virtual rSocket   getSocket() const;

public:
    short int getPort() const;
    std::string const& getAddr() const;

    void setPort(short int port);
    void setAddr(std::string const& addr);

private:
    TcpSocket(TcpSocket const& sock) = delete;
    TcpSocket& operator=(TcpSocket const& sock) = delete;

private:
    short int   _port;
    std::string _addr;
    rSocket     _socket;
};

#endif //RTYPE_TCPSOCKET_HPP
