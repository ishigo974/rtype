//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_ISOCKETMONITOR_HPP
#define RTYPE_ISOCKETMONITOR_HPP

#include "ITcpSocket.hpp"

class ISocketMonitor
{
public:
    virtual ~ISocketMonitor() {}

public:
    virtual void registerSocket(ITcpSocket* socket) = 0;
    virtual void deleteSocket(ITcpSocket* socket) = 0;
    virtual bool isMonitored(ITcpSocket* socket) const = 0;
    virtual int update() const = 0;
};


#endif //RTYPE_ISOCKETMONITOR_HPP
