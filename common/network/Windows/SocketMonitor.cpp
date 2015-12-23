//
// Created by Denis Le Borgne on 14/12/2015.
//

#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include "SocketMonitor.hpp"

/*
** Static variables
*/
const long                          SocketMonitor::defaultSecVal  = 5;
const long                          SocketMonitor::defaultUsecVal = 0;
const unsigned int                  SocketMonitor::noFd           = 0;
SocketMonitor::UniqueMonitorPtr     SocketMonitor::instance;

/*
** Constructor/Destructor
*/
SocketMonitor::SocketMonitor() :
        _secValue(defaultSecVal), _usecValue(defaultUsecVal), _maxFd(noFd)
{
    _eventTotal = 0;
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
    HANDLE NewEvent = 0;

    _socketArray.push_back(id);
    if (id == 0)
    {
        if ((NewEvent = GetStdHandle(STD_INPUT_HANDLE)) == INVALID_HANDLE_VALUE)
            throw std::runtime_error("Can't create event.");
        if (NewEvent == NULL)
            throw std::runtime_error("NULL Event.");
    }
    else
    {
        if ((NewEvent = WSACreateEvent()) == WSA_INVALID_EVENT)
            throw std::runtime_error("Can't create event.");
        if (WSAEventSelect(_socketArray[_eventTotal], NewEvent, FD_ACCEPT |
                                                                FD_CLOSE |
                                                                FD_READ) ==
            SOCKET_ERROR)
            throw std::runtime_error("Event Select failed.");
    }
    _eventArray.push_back(NewEvent);
    ++_eventTotal;
}

void SocketMonitor::registerSocket(IMonitorable const *socket)
{
    registerRaw(socket->getSocket());
}

void SocketMonitor::deleteRaw(rSocket id)
{
    for (DWORD i = 0; i < _eventTotal; i++)
    {
        if (_socketArray[i] == id)
        {
            _socketArray.erase(_socketArray.begin() + i);
            _eventArray.erase(_eventArray.begin() + i);
            --_eventTotal;
            break;
        }
    }
}

void SocketMonitor::deleteSocket(IMonitorable const *socket)
{
    deleteRaw(socket->getSocket());
}

bool SocketMonitor::isWritable(rSocket id)
{
    return true;
}

bool SocketMonitor::isWritable(IMonitorable const *socket)
{
    return isWritable(socket->getSocket());
}

bool SocketMonitor::isReadable(rSocket id)
{
    return ((_socketEvents[id].lNetworkEvents & FD_READ)
            || (_socketEvents[id].lNetworkEvents & FD_CLOSE)
            || (_socketEvents[id].lNetworkEvents & FD_ACCEPT));
}

bool SocketMonitor::isReadable(IMonitorable const *socket)
{
    return isReadable(socket->getSocket());
}

void SocketMonitor::clearFds()
{
}

void SocketMonitor::update()
{
    DWORD            index;
    WSANETWORKEVENTS NetworkEvents;

    _socketEvents.clear();
    index = WSAWaitForMultipleEvents(_eventTotal, _eventArray.data(), FALSE,
                                     _secValue, FALSE);
    index = index - WSA_WAIT_EVENT_0;
    if ((index != WSA_WAIT_FAILED) && (index != WSA_WAIT_TIMEOUT))
        for (DWORD i = 0; i < _eventTotal; i++)
        {
            index = WSAWaitForMultipleEvents(1, &_eventArray[i], TRUE, 1000,
                                             FALSE);
            if ((index != WSA_WAIT_FAILED) && (index != WSA_WAIT_TIMEOUT))
            {
                if (WSAEnumNetworkEvents(_socketArray[i], _eventArray[i],
                                         &NetworkEvents) != SOCKET_ERROR)
                    _socketEvents.insert(std::pair<rSocket, WSANETWORKEVENTS>(
                            _socketArray[i], NetworkEvents));
            }
        }
}

void SocketMonitor::setSec(long value)
{
    _secValue = value;
}

void SocketMonitor::setUsec(long value)
{
    _usecValue = value;
}


std::string SocketMonitor::toString() const
{
    std::string ss;

    ss += "SocketMonitor {";
    ss += "\n\t_fdMax: ";
    ss += _maxFd;
    ss += "\n\t_secValue ";
    ss += std::to_string(_secValue);
    ss += "\n\t_usecValue ";
    ss += std::to_string(_usecValue);
    ss += "\n}\n";
    return ss;
}
