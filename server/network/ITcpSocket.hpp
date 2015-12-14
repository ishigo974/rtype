//
// Created by Denis Le Borgne on 23/11/2015.
//

#ifndef RTYPE_ITCPSOCKET_HPP
#define RTYPE_ITCPSOCKET_HPP

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
#include <sys/select.h>
#endif
#include "ISocket.hpp"

class ITcpSocket : public ISocket
{
public:
    virtual ~ITcpSocket()
    { }
};

#endif //RTYPE_ITCPSOCKET_HPP
