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
    virtual size_t      send(Buffer const *buffer) const;
    virtual Buffer const *recv() const;
    virtual void         close() const;

public:
    virtual bool bind() const;

public:
    virtual std::string toString() const;

public:
    int       getSocket() const; //DO TO TYPEDEF FOR SOCKET
    short int getPort() const;

    void setPort(short int port);

private:
    UdpSocket(UdpSocket const& sock) = delete;
    UdpSocket& operator=(UdpSocket const& sock) = delete;

private:
    short int _port;
    int       _socket;//DO TO TYPEDEF FOR SOCKET
};

#endif //RTYPE_UDPSOCKET_HPP
