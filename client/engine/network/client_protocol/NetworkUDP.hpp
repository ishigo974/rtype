//
// Created by Denis Le Borgne on 20/12/2015.
//

#ifndef RTYPE_NETWORKUDP_HPP
#define RTYPE_NETWORKUDP_HPP


#include "Component.hpp"
#include "Buffer.hpp"
#include "InGameEvent.hpp"

namespace RType
{
    class NetworkUDP
    {
    public:
        static RTypes::my_uint16_t const Mask = ComponentMask::UDPMask;

    public:
        NetworkUDP();
        virtual ~NetworkUDP();

    public:
        virtual RTypes::my_uint16_t getMask() const;

    public:
        Buffer      toSend();
        void        receive(Buffer const& buffer);
        void        pushRequest(InGameEvent const& request);
        InGameEvent popRequest();

    private:
        NetworkUDP(NetworkUDP const&) = delete;
        NetworkUDP& operator=(NetworkUDP const&) = delete;

    private:
        Buffer _send;
        Buffer _receive;
    };
}
#endif //RTYPE_NETWORKUDP_HPP
