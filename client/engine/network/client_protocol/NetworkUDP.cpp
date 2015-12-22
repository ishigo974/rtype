//
// Created by Denis Le Borgne on 20/12/2015.
//

#include <iostream>
#include "NetworkUDP.hpp"
#include "IncompleteRequest.hpp"

namespace RType
{
    NetworkUDP::NetworkUDP()
    { }

    NetworkUDP::~NetworkUDP()
    { }

    RTypes::my_uint16_t NetworkUDP::getMask() const
    {
        return Mask;
    }

    Buffer NetworkUDP::toSend()
    {
        Buffer ret(_send);

        _send.clear();
        return ret;
    }

    void NetworkUDP::receive(Buffer const& buffer)
    {
        _receive.append(buffer);
    }

    void NetworkUDP::pushRequest(InGameEvent const& request)
    {
        _send.append<Buffer>(request.toBuffer());
    }

    InGameEvent NetworkUDP::popRequest()
    {
        if (_receive.empty())
            throw Exception::IncompleteRequest("Empty buffer");
        InGameEvent ret(_receive);
        _receive.consume(ret.toBuffer().size());
        return ret;
    }
}