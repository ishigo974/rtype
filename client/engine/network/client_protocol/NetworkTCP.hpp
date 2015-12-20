//
// Created by Denis Le Borgne on 18/12/2015.
//

#ifndef RTYPE_SERVER_NETWORKTCP_HPP
#define RTYPE_SERVER_NETWORKTCP_HPP

#include <queue>
#include "Request.hpp"
#include "TcpConnector.hpp"
#include "Component.hpp"
#include "REnums.hpp"
#include "RTypes.hpp"

namespace RType
{
    class NetworkTCP : public Component
    {
    public:
        static RTypes::my_uint16_t const Mask = ComponentMask::TCPMask;

    public:
        NetworkTCP(unsigned _id, std::string const& _name);
        virtual ~NetworkTCP();

    public:
        virtual RTypes::my_uint16_t getMask() const;

    public:
        Buffer toSend();
        void   receive(Buffer const& buffer);
        void   pushRequest(Request const& request);
        Request popRequest();

    private:
        NetworkTCP(NetworkTCP const&) = delete;
        NetworkTCP& operator=(NetworkTCP const&) = delete;

    private:
        Buffer _send;
        Buffer _receive;
    };
}

#endif //RTYPE_SERVER_NETWORKTCP_HPP
