//
// Created by Denis Le Borgne on 23/11/2015.
//

#include <algorithm>
#include <ctime>
#include "SocketMonitor.hpp"
#include "TcpSocket.hpp"

SocketMonitor::SocketMonitor()
{
    _secValue  = 2;
    _usecValue = 0;
}

void SocketMonitor::deleteSocket(ITcpSocket *socket)
{
    socket->deleteFromMonitor(&_readFds);
    socket->deleteFromMonitor(&_writeFds);
    _socketList.erase(std::find(_socketList.begin(), _socketList.end(),
                                static_cast<TcpSocket *>(socket)->getAddr()));
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
}

int SocketMonitor::update() const
{
    struct timeval tv;

    tv.tv_sec  = _secValue;
    tv.tv_usec = _usecValue;

    return ::select(_socketList.size() + 1, &_readFds, &_writeFds, NULL, &tv);
}

void SocketMonitor::setSec(int value)
{
    _secValue = value;
}

void SocketMonitor::setUsec(int value)
{
    _usecValue = value;
}
