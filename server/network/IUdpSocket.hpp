//
// Created by Denis Le Borgne on 18/11/2015.
//

#ifndef RTYPE_IUDPSOCKET_HPP
#define RTYPE_IUDPSOCKET_HPP

# include "ISocket.hpp"

class IUdpSocket : public ISocket
{
public:
    virtual ~IUdpSocket() {}

public:
    bool bind() const = 0;
};

#endif //RTYPE_IUDPSOCKET_HPP
