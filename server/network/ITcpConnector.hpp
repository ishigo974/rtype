//
// Created by Denis Le Borgne on 06/12/2015.
//

#ifndef RTYPE_SERVER_ITCPCONNECTOR_HPP
#define RTYPE_SERVER_ITCPCONNECTOR_HPP

#include "ISocket.hpp"

class ITcpConnector : public ISocket
{
public:
    ~ITcpConnector() {}

public:
    virtual bool    connect() = 0;
};


#endif //RTYPE_SERVER_ITCPCONNECTOR_HPP
