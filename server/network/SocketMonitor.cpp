#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#endif

#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include "SocketMonitor.hpp"

/*
** Static variables
*/
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
const long			SocketMonitor::defaultSecVal = 5;
const long			SocketMonitor::defaultUsecVal = 0;
#else
const time_t        SocketMonitor::defaultSecVal  = 5;
const suseconds_t   SocketMonitor::defaultUsecVal = 0;
#endif
const unsigned int                  SocketMonitor::noFd = 0;
SocketMonitor::UniqueMonitorPtr     SocketMonitor::instance;

/*
** Constructor/Destructor
*/
SocketMonitor::SocketMonitor() :
        _secValue(defaultSecVal), _usecValue(defaultUsecVal), _maxFd(noFd)
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
** Static functions
*/
SocketMonitor& SocketMonitor::getInstance()
{
    if (SocketMonitor::instance == nullptr)
        SocketMonitor::instance =
                std::unique_ptr<SocketMonitor>(new SocketMonitor());
    return *SocketMonitor::instance;
}

/*
** Public member functions
*/
void SocketMonitor::registerSocket(IMonitorable const *socket)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
    FD_SET(socket->getSocket(), &_readFds);
    FD_SET(socket->getSocket(), &_writeFds);
#endif
if (socket->getSocket() > _maxFd)
        _maxFd = socket->getSocket();
}

void SocketMonitor::deleteSocket(IMonitorable const *socket)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
    FD_CLR(socket->getSocket(), &_readFds);
    FD_CLR(socket->getSocket(), &_writeFds);
#endif
    if (socket->getSocket() == _maxFd)
        --_maxFd;
}

bool SocketMonitor::isWritable(IMonitorable const *socket)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSANETWORKEVENTS NetworkEvents;
    HANDLE NewEvent = 0;
    rSocket tmp = socket->getSocket();
    DWORD index;

    NewEvent = WSACreateEvent();
    WSAEventSelect(tmp, NewEvent, FD_WRITE | FD_CLOSE);
    index = WSAWaitForMultipleEvents(1, &NewEvent, TRUE, 1000, FALSE);
    if ((index != WSA_WAIT_FAILED) && (index != WSA_WAIT_TIMEOUT))
     {
	    WSAEnumNetworkEvents(tmp, NewEvent, &NetworkEvents);
        if(NetworkEvents.lNetworkEvents & FD_CLOSE)
            return false;
        if(NetworkEvents.lNetworkEvents & FD_WRITE)
            return true;
     }
    return true;
#else
    return FD_ISSET(socket->getSocket(), &_tmpWriteFds) > 0;
#endif
}

bool SocketMonitor::isReadable(IMonitorable const *socket)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    WSANETWORKEVENTS NetworkEvents;
    HANDLE NewEvent = 0;
    rSocket tmp = socket->getSocket();
    DWORD index;

    NewEvent = WSACreateEvent();
    WSAEventSelect(tmp, NewEvent, FD_ACCEPT | FD_READ | FD_CLOSE);
    index = WSAWaitForMultipleEvents(1, &NewEvent, TRUE, 1000, FALSE);
    if ((index != WSA_WAIT_FAILED) && (index != WSA_WAIT_TIMEOUT))
     {
	    WSAEnumNetworkEvents(tmp, NewEvent, &NetworkEvents);
        if(NetworkEvents.lNetworkEvents & FD_CLOSE)
            return true;
        if(NetworkEvents.lNetworkEvents & FD_READ)
            return true;
        if(NetworkEvents.lNetworkEvents & FD_ACCEPT)
			return true;
     }
    return false;
#else
    return FD_ISSET(socket->getSocket(), &_tmpReadFds) > 0;
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

    tv.tv_sec  = _secValue;
    tv.tv_usec = _usecValue;
    _tmpReadFds  = _readFds;
    _tmpWriteFds = _writeFds;
    if (::select(_maxFd + 1, &_tmpReadFds, &_tmpWriteFds, NULL, &tv) == -1)
        throw std::runtime_error("select failed");
#endif
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
void SocketMonitor::setSec(long value)
{
    _secValue = value;
}

void SocketMonitor::setUsec(long value)
{
    _usecValue = value;
}
#else

void SocketMonitor::setSec(time_t value)
{
    _secValue = value;
}

void SocketMonitor::setUsec(suseconds_t value)
{
    _usecValue = value;
}

#endif

std::string SocketMonitor::toString() const
{
    std::ostringstream ss;

    ss << "SocketMonitor {"
    << "\n\t_fdMax: " << _maxFd
    << "\n\t_secValue " << _secValue
    << "\n\t_usecValue " << _usecValue
    << "\n}" << std::endl;
    return ss.str();
}
