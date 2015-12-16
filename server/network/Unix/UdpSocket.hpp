//
// Created by Denis Le Borgne on 14/12/2015.
//

#ifndef RTYPE_SERVER_UDPSOCKET_HPP
#define RTYPE_SERVER_UDPSOCKET_HPP


# include <string>
# include "IUdpSocket.hpp"
#include "BaseSocket.hpp"

class UdpSocket : public IUdpSocket, public BaseSocket
{
public:
    UdpSocket(short int port);

    virtual ~UdpSocket()
    { }

public:
    virtual size_t send(Buffer const& buffer) const;
    virtual size_t receive(Buffer& buffer, size_t len) const;
    virtual void   close() const;
    virtual std::string const& getAddr() const;

public:
    virtual bool bind() const;

public:
    virtual std::string toString() const;

public:
    virtual size_t sendTo(Buffer const& buffer, std::string const& addr) const;
    virtual size_t receiveFrom(Buffer& buffer, size_t len, std::string& addr) const;

public:
    rSocket   getSocket() const;
    short int getPort() const;

    void setPort(short int port);

private:
    UdpSocket(UdpSocket const& sock) = delete;
    UdpSocket& operator=(UdpSocket const& sock) = delete;
};

#endif //RTYPE_SERVER_UDPSOCKET_HPP
