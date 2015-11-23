//
// Created by Denis Le Borgne on 19/11/2015.
//

#ifndef RTYPE_ITCPACCEPTOR_HPP
#define RTYPE_ITCPACCEPTOR_HPP

class ITcpAcceptor
{
public:
    virtual ITcpAcceptor() {}

public:
    virtual ISocket const* accept() const = 0;
};

#endif //RTYPE_ITCPACCEPTOR_HPP
