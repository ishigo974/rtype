//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include "SocketMonitor.hpp"
#include "NetTypes.hpp"

/*
** Static variables
*/
const time_t        SocketMonitor::defaultSecVal    = 5;
const suseconds_t   SocketMonitor::defaultUsecVal   = 0;
const unsigned int                  SocketMonitor::noFd = 0;
SocketMonitor::UniqueMonitorPtr     SocketMonitor::instance;

/*
** Constructor/Destructor
*/
SocketMonitor::SocketMonitor() :
        _secValue(defaultSecVal), _usecValue(defaultUsecVal), _maxFd(noFd)
{
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
    FD_ZERO(&_tmpReadFds);
    FD_ZERO(&_tmpWriteFds);
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
void SocketMonitor::registerRaw(rSocket id)
{
    FD_SET(id, &_readFds);
    FD_SET(id, &_writeFds);
    if (static_cast<int>(id) > _maxFd)
        _maxFd = id;
}

void SocketMonitor::registerSocket(IMonitorable const *socket)
{
    registerRaw(socket->getSocket());
}

void SocketMonitor::deleteRaw(rSocket id)
{
    FD_CLR(id, &_readFds);
    FD_CLR(id, &_writeFds);
    if (static_cast<int>(id) == _maxFd)
        --_maxFd;
}

void SocketMonitor::deleteSocket(IMonitorable const *socket)
{
    deleteRaw(socket->getSocket());
}

bool SocketMonitor::isWritable(rSocket id)
{
    return FD_ISSET(id, &_tmpWriteFds) > 0;
}

bool SocketMonitor::isWritable(IMonitorable const *socket)
{
    return isWritable(socket->getSocket());
}

bool SocketMonitor::isReadable(rSocket id)
{
    return FD_ISSET(id, &_tmpReadFds) > 0;
}

bool SocketMonitor::isReadable(IMonitorable const *socket)
{
    return isReadable(socket->getSocket());
}

void SocketMonitor::clearFds()
{
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
    FD_ZERO(&_tmpReadFds);
    FD_ZERO(&_tmpWriteFds);
}

void SocketMonitor::update()
{
    struct timeval tv;

    tv.tv_sec  = _secValue;
    tv.tv_usec = _usecValue;
    _tmpReadFds  = _readFds;
    _tmpWriteFds = _writeFds;
    if (::select(_maxFd + 1, &_tmpReadFds, &_tmpWriteFds, NULL, &tv) == -1)
        throw std::runtime_error("select failed");
}


void SocketMonitor::setSec(time_t value)
{
    _secValue = value;
}

void SocketMonitor::setUsec(suseconds_t value)
{
    _usecValue = value;
}

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
