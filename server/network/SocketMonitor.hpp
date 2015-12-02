//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_SOCKETMONITOR_HPP
#define RTYPE_SOCKETMONITOR_HPP

#include <string>
#include <vector>
#include <memory>
#include "IStringable.hpp"
#include "IMonitorable.hpp"

class SocketMonitor : public IStringable
{
public:
    typedef std::unique_ptr<SocketMonitor>          UniqueMonitorPtr;

protected:
    SocketMonitor();

public:
    virtual ~SocketMonitor();

private:
    SocketMonitor(SocketMonitor const& monitor) = delete;
    SocketMonitor& operator=(SocketMonitor const& monitor) = delete;

public:
    static SocketMonitor&   getInstance();

public:
    void    registerSocket(IMonitorable const* socket);
    void    deleteSocket(IMonitorable const* socket);
    bool    isReadable(IMonitorable const* socket);
    bool    isWritable(IMonitorable const* socket);
    void    clearFds();
    void    update();

public:
    void    setSec(time_t value);
    void    setUsec(suseconds_t value);

public:
    virtual std::string toString() const;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
    private:
        fd_set      _readFds;
        fd_set      _writeFds;
        fd_set      _tmpReadFds;
        fd_set      _tmpWriteFds;
#endif

private:
    time_t          _secValue;
    suseconds_t     _usecValue;
    rSocket         _maxFd;

public:
    static const time_t             defaultSecVal;
    static const suseconds_t        defaultUsecVal;
    static const unsigned int       noFd;

protected:
    static UniqueMonitorPtr     instance;
};


#endif //RTYPE_SOCKETMONITOR_HPP
