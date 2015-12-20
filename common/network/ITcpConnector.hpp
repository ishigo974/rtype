//
// Created by Denis Le Borgne on 06/12/2015.
//

#ifndef RTYPE_SERVER_ITCPCONNECTOR_HPP
#define RTYPE_SERVER_ITCPCONNECTOR_HPP

#include "ITcpSocket.hpp"

class ITcpConnector
{
public:
    virtual ~ITcpConnector()
    { }

public:
    virtual void connect() = 0;
};


#endif //RTYPE_SERVER_ITCPCONNECTOR_HPP
