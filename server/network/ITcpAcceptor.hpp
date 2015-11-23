//
// Created by Denis Le Borgne on 19/11/2015.
//

#ifndef RTYPE_ITCPACCEPTOR_HPP
#define RTYPE_ITCPACCEPTOR_HPP

#include "ITcpSocket.hpp"

class ITcpAcceptor: public ITcpSocket
{
public:
    virtual ~ITcpAcceptor()
    { }

public:
    virtual ITcpSocket const *accept() const = 0;

public:
    virtual void registerToMonitor(fd_set *fdSet) const = 0;
    virtual void deleteFromMonitor(fd_set *fdSet) const = 0;
};

#endif //RTYPE_ITCPACCEPTOR_HPP
