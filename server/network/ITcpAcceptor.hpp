//
// Created by Denis Le Borgne on 19/11/2015.
//

#ifndef RTYPE_ITCPACCEPTOR_HPP
#define RTYPE_ITCPACCEPTOR_HPP

#include "ITcpSocket.hpp"

class ITcpAcceptor : public ITcpSocket
{
public:
    virtual ~ITcpAcceptor()
    { }

public:
    virtual ITcpSocket *accept() const = 0;
};

#endif //RTYPE_ITCPACCEPTOR_HPP
