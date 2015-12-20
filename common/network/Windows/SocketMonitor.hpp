//
// Created by Denis Le Borgne on 14/12/2015.
//

#ifndef RTYPE_SERVER_SOCKETMONITOR_HPP
#define RTYPE_SERVER_SOCKETMONITOR_HPP


#include <string>
#include <vector>
#include <memory>
#include <map>
#include "ISocketMonitor.hpp"

class SocketMonitor : public ISocketMonitor
{
public:
    typedef std::unique_ptr<SocketMonitor> UniqueMonitorPtr;

    SocketMonitor();

public:
    virtual ~SocketMonitor();

private:
    SocketMonitor(SocketMonitor const& monitor) = delete;
    SocketMonitor& operator=(SocketMonitor const& monitor) = delete;

public:
    static SocketMonitor& getInstance();

public:
    virtual void registerRaw(rSocket id);
    virtual void registerSocket(IMonitorable const *socket);
    virtual void deleteRaw(rSocket id);
    virtual void deleteSocket(IMonitorable const *socket);
    virtual bool isReadable(rSocket id);
    virtual bool isReadable(IMonitorable const *socket);
    virtual bool isWritable(IMonitorable const *socket);
    virtual bool isWritable(rSocket id);
    virtual void clearFds();
    virtual void update();

public:
    void setSec(long value);
    void setUsec(long value);

public:
    virtual std::string toString() const;

private:
    DWORD                               _eventTotal;
    std::vector<HANDLE>                 _eventArray;
    std::vector<rSocket>                _socketArray;
    std::map<rSocket, WSANETWORKEVENTS> _socketEvents;

private:
    long    _secValue;
    long    _usecValue;
    rSocket _maxFd;

public:
    static const long         defaultSecVal;
    static const long         defaultUsecVal;
    static const unsigned int noFd;

protected:
    static UniqueMonitorPtr instance;
};


#endif //RTYPE_SERVER_SOCKETMONITOR_HPP
