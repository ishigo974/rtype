#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#endif

#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include "SocketMonitor.hpp"
#include "TcpSocket.hpp"

/*
** Static variables
*/
const time_t        SocketMonitor::defaultSecVal  = 5;
const suseconds_t   SocketMonitor::defaultUsecVal = 0;

/*
** Constructor/Destructor
*/
SocketMonitor::SocketMonitor() :
    _secValue(defaultSecVal), _usecValue(defaultUsecVal), _maxFd(0)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #else
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
    FD_ZERO(&_tmpReadFds);
    FD_ZERO(&_tmpWriteFds);
    #endif
}

SocketMonitor::~SocketMonitor()
{
}

/*
** Public member functions
*/
void SocketMonitor::registerSocket(IMonitorable const* socket)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #else
    FD_SET(socket->getSocket(), &_readFds);
    FD_SET(socket->getSocket(), &_writeFds);
    #endif

    if (socket->getSocket() > _maxFd)
    _maxFd = socket->getSocket();
}

void SocketMonitor::deleteSocket(IMonitorable const* socket)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #else
    FD_CLR(socket->getSocket(), &_readFds);
    FD_CLR(socket->getSocket(), &_writeFds);
    #endif

    if (socket->getSocket() == _maxFd)
    --_maxFd;
}

bool SocketMonitor::isWritable(IMonitorable const* socket)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    return true;
    #else
    return FD_ISSET(socket->getSocket(), &_tmpWriteFds) != 0;
    #endif
}

bool SocketMonitor::isReadable(IMonitorable const* socket)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    return true;
    #else
    return FD_ISSET(socket->getSocket(), &_tmpReadFds) != 0;
    #endif
}

void SocketMonitor::clearFds()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #else
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
    FD_ZERO(&_tmpReadFds);
    FD_ZERO(&_tmpWriteFds);
    #endif
}

void SocketMonitor::update()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #else
    struct timeval tv;

    tv.tv_sec = _secValue;
    tv.tv_usec = _usecValue;
    _tmpReadFds = _readFds;
    _tmpWriteFds = _writeFds;
    if (select(_maxFd + 1, &_tmpReadFds, &_tmpWriteFds, NULL, &tv) == -1)
    throw std::runtime_error("select failed");
    #endif
}

void SocketMonitor::setSec(int value)
{
    _secValue = value;
}

void SocketMonitor::setUsec(int value)
{
    _usecValue = value;
}

std::string SocketMonitor::toString() const
{
    std::ostringstream ss;

    ss  << "SocketMonitor {"
    << "\n\t_fdMax: " << _maxFd
    << "\n\t_secValue " << _secValue
    << "\n\t_usecValue " << _usecValue
    << std::endl;
    return ss.str();
}
