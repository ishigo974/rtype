//
// Created by Denis Le Borgne on 23/11/2015.
//

#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include "SocketMonitor.hpp"
#include "TcpSocket.hpp"

int SocketMonitor::defaultSecVal  = 5;
int SocketMonitor::defaultUsecVal = 0;

SocketMonitor::SocketMonitor()
{
    _secValue  = SocketMonitor::defaultSecVal;
    _usecValue = SocketMonitor::defaultUsecVal;

    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
}

SocketMonitor::~SocketMonitor()
{ }

void SocketMonitor::deleteSocket(ITcpSocket *socket)
{
    std::vector<std::string>::iterator it;

    it = _socketList.begin();
    socket->deleteFromMonitor(&_readFds);
    socket->deleteFromMonitor(&_writeFds);
    if ((it = std::find(_socketList.begin(), _socketList.end(),
                        static_cast<TcpSocket *>(socket)->getAddr()))
        == _socketList.end())
        return;
    _socketList.erase(it);
}

bool SocketMonitor::isWritable(ITcpSocket *socket)
{
    return FD_ISSET(socket->getSocket(), &_writeFds) > 0;
}

bool SocketMonitor::isReadable(ITcpSocket *socket)
{
    return FD_ISSET(socket->getSocket(), &_readFds) > 0;
}

void SocketMonitor::clearFds()
{
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
    _socketList.erase(_socketList.begin(), _socketList.end());
    _maxFd = 0;
}

void SocketMonitor::registerSocket(ITcpSocket *socket)
{
    socket->registerToMonitor(&_readFds, &_maxFd);
    socket->registerToMonitor(&_writeFds, &_maxFd);
    _socketList.insert(_socketList.end(), static_cast<TcpSocket *>(socket)
            ->getAddr());
}

int SocketMonitor::update()
{
    struct timeval tv;

    tv.tv_sec  = _secValue;
    tv.tv_usec = _usecValue;

    return ::select(_maxFd + 1, &_readFds, NULL, NULL, &tv);
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

    ss << "SocketMonitor {"
    << "\n\tFD Max " << this->_maxFd
    << "\n\tTimeout Second " << this->_secValue
    << "\n\tTimeout uSecond " << this->_usecValue
    << "\n\tSocket Addr List [";
    for (auto&& e : _socketList)
        ss << "(" << e.data() << ") ";
    ss << "]\n}" << std::endl;

    return ss.str();
}
