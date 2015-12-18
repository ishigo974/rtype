//
// Created by Denis Le Borgne on 14/12/2015.
//

#ifndef RTYPE_SERVER_UDPSOCKET_HPP
#define RTYPE_SERVER_UDPSOCKET_HPP

# include <string>
# include "IUdpSocket.hpp"
# include "BaseSocket.hpp"

class UdpSocket : public IUdpSocket, public BaseSocket
{
public:
    UdpSocket(short int port);
    virtual ~UdpSocket();

private:
    UdpSocket(UdpSocket const& other) = delete;
    UdpSocket& operator=(UdpSocket const& other) = delete;

public:
    virtual size_t  send(Buffer const& buffer) const;
    virtual size_t  receive(Buffer& buffer, size_t len) const;
    virtual void    close() const;

public:
    virtual bool    bind() const;
    virtual size_t sendTo(Buffer const& buffer, std::string const& addr) const;
    virtual size_t receiveFrom(Buffer& buffer, size_t len,
                                std::string& addr) const;

public:
    virtual std::string toString() const;

public:
    rSocket                     getSocket() const;
    short int                   getPort() const;
    void                        setPort(short int port);
};

#endif //RTYPE_SERVER_UDPSOCKET_HPP
