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
    class NetworkTCP
    {
    public:
        static RTypes::my_uint16_t const Mask = ComponentMask::NetworkMask;

    public:
        NetworkTCP(std::string const&, short int);
        virtual ~NetworkTCP();

    public:
        void    pushRequest(Request const&);
        void    update();
        Request popRequest();
        bool    pendingRequests() const;
        void    connect();
        bool    isConnected() const;

    public:
        static const size_t bufferSize;

    protected:
        void buildRequest();
        void disconnection();

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
