//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_SOCKETMONITOR_HPP
#define RTYPE_SOCKETMONITOR_HPP

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
    virtual void registerRaw(unsigned int id);
    virtual void registerSocket(IMonitorable const *socket);
    virtual void deleteRaw(unsigned int id);
    virtual void deleteSocket(IMonitorable const *socket);
    virtual bool isReadable(unsigned int id);
    virtual bool isReadable(IMonitorable const *socket);
    virtual bool isWritable(IMonitorable const *socket);
    virtual bool isWritable(unsigned int id);
    virtual void clearFds();
    virtual void update();

public:
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    void    setSec(long value);
    void    setUsec(long value);
#else
    void setSec(time_t value);
    void setUsec(suseconds_t value);
#endif

public:
    virtual std::string toString() const;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
private:
    DWORD                       _eventTotal;
    std::vector<HANDLE>       _eventArray;
    std::vector<rSocket>                _socketArray;
    std::map<rSocket, WSANETWORKEVENTS> _socketEvents;

#else
private:
    fd_set _readFds;
    fd_set _writeFds;
    fd_set _tmpReadFds;
    fd_set _tmpWriteFds;
#endif

private:
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    long	_secValue;
    long    _usecValue;
#else
    time_t      _secValue;
    suseconds_t _usecValue;
#endif
    rSocket _maxFd;

public:
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    static const long			defaultSecVal;
    static const long			defaultUsecVal;
#else
    static const time_t      defaultSecVal;
    static const suseconds_t defaultUsecVal;
#endif
    static const unsigned int noFd;

protected:
    static UniqueMonitorPtr instance;
};


#endif //RTYPE_SOCKETMONITOR_HPP
