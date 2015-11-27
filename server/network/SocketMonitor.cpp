//
// Created by Denis Le Borgne on 23/11/2015.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#endif
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
	_maxFd = 0;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
	FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
#endif
}

SocketMonitor::~SocketMonitor()
{ }

void SocketMonitor::deleteSocket(IMonitorable *socket)
{
    std::vector<std::string>::iterator it;

    it = _socketList.begin();
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
	FD_CLR(socket->getSocket(), &_readFds);
	FD_CLR(socket->getSocket(), &_writeFds);
#endif
	if ((it = std::find(_socketList.begin(), _socketList.end(),
                        static_cast<TcpSocket *>(socket)->getAddr()))
        == _socketList.end())
        return;
    _socketList.erase(it);
}

void SocketMonitor::registerSocket(IMonitorable *socket)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
	FD_SET(socket->getSocket(), &_readFds);
	FD_SET(socket->getSocket(), &_readFds);
#endif
	_socketList.insert(_socketList.end(), static_cast<TcpSocket *>(socket)
		->getAddr());
}

bool SocketMonitor::isWritable(IMonitorable *socket)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	return true;
#else
    return FD_ISSET(socket->getSocket(), &_writeFds) > 0;
#endif
}

bool SocketMonitor::isReadable(IMonitorable *socket)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	return true;
#else
    return FD_ISSET(socket->getSocket(), &_readFds) > 0;
#endif
}

void SocketMonitor::clearFds()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
#endif
    _socketList.erase(_socketList.begin(), _socketList.end());
    _maxFd = 0;
}

int SocketMonitor::update()
{

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	return 0;
#else
	struct timeval tv;

	tv.tv_sec = _secValue;
	tv.tv_usec = _usecValue;

    return ::select(_maxFd + 1, &_readFds, NULL, NULL, &tv);
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
