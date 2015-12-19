//
// Created by Denis Le Borgne on 18/12/2015.
//

#include "NetworkTCP.hpp"

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
}