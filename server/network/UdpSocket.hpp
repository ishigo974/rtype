//
// Created by Denis Le Borgne on 18/11/2015.
//

#ifndef RTYPE_UDPSOCKET_HPP
# define RTYPE_UDPSOCKET_HPP

# include <string>
# include "IUdpSocket.hpp"

class UdpSocket : public IUdpSocket
{
public:
    UdpSocket(short int port);

    virtual ~UdpSocket()
    { }

public:
    virtual size_t    send(Buffer const& buffer) const;
    virtual size_t    receive(Buffer& buffer, size_t len) const;
    virtual void      close() const;

public:
    virtual bool bind() const;

public:
    virtual std::string toString() const;

public:
    rSocket   getSocket() const;
    short int getPort() const;

    void setPort(short int port);

private:
    UdpSocket(UdpSocket const& sock) = delete;
    UdpSocket& operator=(UdpSocket const& sock) = delete;

private:
    short int _port;
    rSocket   _socket;
};

#endif //RTYPE_UDPSOCKET_HPP
