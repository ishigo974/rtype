//
// Created by Denis Le Borgne on 14/12/2015.
//

#ifndef RTYPE_SERVER_BASESOCKET_HPP
#define RTYPE_SERVER_BASESOCKET_HPP

#include "IStringable.hpp"
#include "Buffer.hpp"
#include "NetTypes.hpp"

class BaseSocket
{
public:

    BaseSocket();
    virtual ~BaseSocket();

public:
    virtual size_t send(Buffer const& buffer) const;
    virtual size_t receive(Buffer& buffer, size_t len) const;
    virtual void   close() const;

protected:
    rSocket   _socket;
    short int _port;
};


#endif //RTYPE_SERVER_BASESOCKET_HPP