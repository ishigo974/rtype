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
    const long			SocketMonitor::defaultSecVal   = 5;
    const long			SocketMonitor::defaultUsecVal  = 0;
#else
    const time_t        SocketMonitor::defaultSecVal    = 5;
    const suseconds_t   SocketMonitor::defaultUsecVal   = 0;
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
    _eventTotal = 0;
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
void SocketMonitor::registerRaw(unsigned int id)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    HANDLE NewEvent = 0;

    NewEvent = WSACreateEvent();
    _socketArray.push_back(id);
    WSAEventSelect(_socketArray[_eventTotal], NewEvent, FD_ACCEPT |
                   FD_CLOSE | FD_READ);
    _eventArray.push_back(NewEvent);
    ++_eventTotal;
#else
    FD_SET(id, &_readFds);
    FD_SET(id, &_writeFds);
#endif
    if (static_cast<int>(id) > _maxFd)
        _maxFd = id;
}

void SocketMonitor::registerSocket(IMonitorable const *socket)
{
    registerRaw(socket->getSocket());
}

void SocketMonitor::deleteRaw(unsigned int id)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    for (DWORD i = 0; i < _eventTotal; i++)
    {
        if (_socketArray[i] == id)
        {
            _socketArray.erase(_socketArray.begin() + i);
            _eventArray.erase(_eventArray.begin() + i);
            --_eventTotal;
            break ;
        }
    }
#else
    FD_CLR(id, &_readFds);
    FD_CLR(id, &_writeFds);
#endif
    if (static_cast<int>(id) == _maxFd)
        --_maxFd;
}

void SocketMonitor::deleteSocket(IMonitorable const *socket)
{
    deleteRaw(socket->getSocket());
}

bool SocketMonitor::isWritable(unsigned int id)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    return true;
#else
    return FD_ISSET(id, &_tmpWriteFds) > 0;
#endif
}

bool SocketMonitor::isWritable(IMonitorable const *socket)
{
    return isWritable(socket->getSocket());
}

bool SocketMonitor::isReadable(unsigned int id)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

    return (_socketEvents[id].lNetworkEvents & FD_READ)
            || (_socketEvents[id].lNetworkEvents & FD_CLOSE)
            || (_socketEvents[id].lNetworkEvents & FD_ACCEPT);
#else
    return FD_ISSET(id, &_tmpReadFds) > 0;
#endif
}

bool SocketMonitor::isReadable(IMonitorable const *socket)
{
    return isReadable(socket->getSocket());
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
    DWORD index;
    WSANETWORKEVENTS NetworkEvents;

    _socketEvents.clear();
    index = WSAWaitForMultipleEvents(_eventTotal, _eventArray.data(), FALSE,
    SocketMonitor::defaultSecVal, FALSE);
    index = index - WSA_WAIT_EVENT_0;
  if ((index != WSA_WAIT_FAILED) && (index != WSA_WAIT_TIMEOUT))
   for (DWORD i = 0; i < _eventTotal; i++)
   {
	    index = WSAWaitForMultipleEvents(1, &_eventArray[i], TRUE, 1000, FALSE);
        if ((index != WSA_WAIT_FAILED) && (index != WSA_WAIT_TIMEOUT))
        {
            if (WSAEnumNetworkEvents(_socketArray[i], _eventArray[i],
            &NetworkEvents) == SOCKET_ERROR)
            _socketEvents.insert(std::pair<rSocket, WSANETWORKEVENTS>
            (_socketArray[i], NetworkEvents));
        }
   }
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
