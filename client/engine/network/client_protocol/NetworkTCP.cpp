//
// Created by Denis Le Borgne on 18/12/2015.
//

#include <iostream>
#include "NetworkTCP.hpp"
#include "IncompleteRequest.hpp"

namespace RType
{
    NetworkTCP::NetworkTCP()
    { }

    NetworkTCP::~NetworkTCP()
    {
    }

    RTypes::my_uint16_t NetworkTCP::getMask() const
    {
        return Mask;
    }

    Buffer NetworkTCP::toSend()
    {
        Buffer ret(_send);

        _send.clear();
        return ret;
    }

    void NetworkTCP::receive(Buffer const& buffer)
    {
        _receive.append(buffer);
    }

    void NetworkTCP::pushRequest(Request const& request)
    {
        _send.append(request.toBuffer());
    }

    Request NetworkTCP::popRequest()
    {
        if (_receive.empty())
            throw Exception::IncompleteRequest("Empty buffer");

        Request ret(_receive);
        _receive.consume(ret.toBuffer().size());

        return ret;
    }

    size_t NetworkTCP::inSize() const
    {
        return (_receive.size());
    }
}