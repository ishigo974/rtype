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
    void setSec(time_t value);
    void setUsec(suseconds_t value);

public:
    virtual std::string toString() const;

private:
    fd_set _readFds;
    fd_set _writeFds;
    fd_set _tmpReadFds;
    fd_set _tmpWriteFds;
    time_t      _secValue;
    suseconds_t _usecValue;

    rSocket _maxFd;

public:
    static const time_t      defaultSecVal;
    static const suseconds_t defaultUsecVal;
    static const unsigned int noFd;

protected:
    static UniqueMonitorPtr instance;
};

#endif //RTYPE_SERVER_SOCKETMONITOR_HPP
