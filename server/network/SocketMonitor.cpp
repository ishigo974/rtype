//
// Created by Denis Le Borgne on 23/11/2015.
//

#include <algorithm>
#include <ctime>
#include "SocketMonitor.hpp"
#include "TcpSocket.hpp"

int SocketMonitor::defaultSecVal  = 2;
int SocketMonitor::defaultUsecVal = 0;

SocketMonitor::SocketMonitor()
{
    _secValue = SocketMonitor::defaultSecVal;
    _usecValue = SocketMonitor::defaultUsecVal;
    _size = 0;

    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
}

SocketMonitor::~SocketMonitor()
{ }

void SocketMonitor::deleteSocket(ITcpSocket *socket)
{
    std::vector<std::string>::iterator it;

    socket->deleteFromMonitor(&_readFds);
    socket->deleteFromMonitor(&_writeFds);
    if ((it = std::find(_socketList.begin(), _socketList.end(),
                        static_cast<TcpSocket *>(socket)->getAddr()))
        == _socketList.end())
        return;
    _socketList.erase(it);
    --_size;
}

bool SocketMonitor::isMonitored(ITcpSocket *socket) const
{
    if (std::find(_socketList.begin(), _socketList.end(),
                  static_cast<TcpSocket *>(socket)->getAddr())
        != _socketList.end())
        return true;
    return false;
}

void SocketMonitor::registerSocket(ITcpSocket *socket)
{
    socket->registerToMonitor(&_readFds);
    socket->registerToMonitor(&_writeFds);
    _socketList.insert(_socketList.end(), static_cast<TcpSocket *>(socket)
            ->getAddr());
    ++_size;
}

int SocketMonitor::update()
{
    struct timeval tv;

    tv.tv_sec  = _secValue;
    tv.tv_usec = _usecValue;

    return ::select(_size + 1, &_readFds, &_writeFds, NULL, &tv);
}

void SocketMonitor::setSec(int value)
{
    _secValue = value;
}

void SocketMonitor::setUsec(int value)
{
    _usecValue = value;
}
