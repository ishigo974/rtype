//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_ISOCKETMONITOR_HPP
#define RTYPE_ISOCKETMONITOR_HPP

#include "IStringable.hpp"
#include "ITcpSocket.hpp"

class ISocketMonitor : public IStringable
{
public:
    virtual ~ISocketMonitor()
    { }

public:
    virtual void registerSocket(ITcpSocket *socket) = 0;
    virtual void deleteSocket(ITcpSocket *socket)   = 0;
    virtual bool isReadable(ITcpSocket *socket)     = 0;
    virtual bool isWritable(ITcpSocket *socket)     = 0;
    virtual void clearFds()                         = 0;
    virtual int  update()                           = 0;
};


#endif //RTYPE_ISOCKETMONITOR_HPP
