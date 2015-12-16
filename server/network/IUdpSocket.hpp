//
// Created by Denis Le Borgne on 18/11/2015.
//

#ifndef RTYPE_IUDPSOCKET_HPP
#define RTYPE_IUDPSOCKET_HPP

# include "ISocket.hpp"

class IUdpSocket : public ISocket
{
public:
    virtual ~IUdpSocket()
    { }

public:
    virtual bool bind() const = 0;

public:
    virtual size_t sendTo(Buffer const& buffer, std::string const& addr)
                           const = 0;
    virtual size_t receiveFrom(Buffer& buffer, size_t len, std::string&
    addr)
                           const = 0;
};

#endif //RTYPE_IUDPSOCKET_HPP
