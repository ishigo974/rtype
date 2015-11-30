//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_SOCKETMONITOR_HPP
#define RTYPE_SOCKETMONITOR_HPP

#include <string>
#include <vector>
#include "ISocketMonitor.hpp"

class SocketMonitor : public ISocketMonitor
{
public:
    virtual ~SocketMonitor();
    SocketMonitor();

public:
    virtual void registerSocket(ITcpSocket *socket);
    virtual void deleteSocket(ITcpSocket *socket);
    virtual bool isReadable(ITcpSocket *socket);
    virtual bool isWritable(ITcpSocket *socket);
    virtual void clearFds();
    virtual int  update();

public:
    virtual std::string toString() const;

public:
    void setSec(int value);
    void setUsec(int value);

private:
    SocketMonitor(SocketMonitor const& monitor) = delete;
    SocketMonitor& operator=(SocketMonitor const& monitor) = delete;

private:
    std::vector<std::string> _socketList;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
    fd_set _readFds;
    fd_set _writeFds;
#endif
    int        _secValue;
    int        _usecValue;
    rSocket    _maxFd;
    static int defaultSecVal;
    static int defaultUsecVal;
};


#endif //RTYPE_SOCKETMONITOR_HPP
