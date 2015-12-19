//
// Created by Denis Le Borgne on 18/12/2015.
//

#ifndef RTYPE_SERVER_NETWORKTCP_HPP
#define RTYPE_SERVER_NETWORKTCP_HPP

#include <queue>
#include "IStringable.hpp"
#include "Request.hpp"
#include "TcpConnector.hpp"
#include "Component.hpp"
#include "../../core/Component.hpp"
#include "../../../lib/REnums.hpp"
#include "../../../lib/RTypes.hpp"

namespace RType
{
    class NetworkTCP : public Component
    {
    public:
        static RTypes::my_uint16_t const Mask = ComponentMask::NetworkMask;

    public:
        NetworkTCP(std::string const&, short int);
        virtual ~NetworkTCP();

    public:
        virtual std::string toString() const;

    public:
        void    pushRequest(Request const&);
        void    update();
        Request popRequest();
        bool    pendingRequests() const;
        void    connect();
        bool    isConnected() const;

    protected:
        void buildRequest();
        void disconnection();

    public:
        static const size_t bufferSize;

    private:
        NetworkTCP(NetworkTCP const&) = delete;
        NetworkTCP& operator=(NetworkTCP const&) = delete;

    private:
        TcpConnector         _connector;
        bool                 _connected;
        std::vector<Request> _toSend;
        std::queue<Request>  _requests;
        Buffer               _receive;
    };
}


#endif //RTYPE_SERVER_NETWORKTCP_HPP
