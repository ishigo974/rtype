//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_ISOCKETMONITOR_HPP
#define RTYPE_ISOCKETMONITOR_HPP

#include "IStringable.hpp"
#include "IMonitorable.hpp"

class ISocketMonitor : public IStringable
{
public:
    virtual ~ISocketMonitor() {}

public:
    virtual void registerSocket(IMonitorable* socket) = 0;
    virtual void deleteSocket(IMonitorable* socket)   = 0;
    virtual bool isReadable(IMonitorable* socket)     = 0;
    virtual bool isWritable(IMonitorable* socket)     = 0;
    virtual void clearFds()                           = 0;
    virtual int  update()                             = 0;
};


#endif //RTYPE_ISOCKETMONITOR_HPP
