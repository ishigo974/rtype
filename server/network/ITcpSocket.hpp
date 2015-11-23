//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_ITCPSOCKET_HPP
#define RTYPE_ITCPSOCKET_HPP

#include <sys/select.h>
#include "ISocket.hpp"

class ITcpSocket : public ISocket
{
public:
    virtual ~ITcpSocket()
    { }

public:
    virtual void registerToMonitor(fd_set *fd) const = 0;
    virtual void deleteFromMonitor(fd_set *fd) const = 0;
};

#endif //RTYPE_ITCPSOCKET_HPP
