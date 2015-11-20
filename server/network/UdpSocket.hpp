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
    UdpSocket(std::string const& addr, short int port);
    virtual ~UdpSocket();

public:
    virtual size_t send(IBuffer const* buffer) const;
    virtual IBuffer* recv() const;
    virtual void close() const;
    virtual bool isReadable() const;
    virtual bool isWritable() const;

    virtual bool bind() const;

public:
    int getSocket() const; //DO TO TYPEDEF FOR SOCKET
    short int getPort() const;
    std::string getAddr() const;

    void setPort(short int port);
    void setAddr(std::string const& add);

private:
    UdpSocket(UdpSocket const& sock) = delete;
    UdpSocket& operator=(UdpSocket const& sock) = delete;

private:
    std::string _addr;
    short int   _port;
    int         _socket;//DO TO TYPEDEF FOR SOCKET
};

#endif //RTYPE_UDPSOCKET_HPP
