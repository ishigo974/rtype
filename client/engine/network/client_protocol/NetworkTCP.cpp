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
}