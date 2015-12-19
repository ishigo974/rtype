//
// Created by Denis Le Borgne on 08/12/2015.
//

#ifndef RTYPE_SERVER_ISOCKETMONITOR_HPP
#define RTYPE_SERVER_ISOCKETMONITOR_HPP

#include "IMonitorable.hpp"
#include "IStringable.hpp"

class ISocketMonitor : public IStringable
{
public:
    virtual ~ISocketMonitor()
    { }

public:
    virtual void registerSocket(IMonitorable const *socket) = 0;
    virtual void deleteSocket(IMonitorable const *socket)   = 0;
    virtual bool isReadable(IMonitorable const *socket)     = 0;
    virtual bool isWritable(IMonitorable const *socket)     = 0;
    virtual void clearFds()                                 = 0;
    virtual void update()                                   = 0;
};

#endif //RTYPE_SERVER_ISOCKETMONITOR_HPP
