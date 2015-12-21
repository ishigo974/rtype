//
// Created by Denis Le Borgne on 18/12/2015.
//

#ifndef RTYPE_SERVER_CLIENTNETWORK_HPP
#define RTYPE_SERVER_CLIENTNETWORK_HPP

#include "NetworkTCP.hpp"
#include "SocketMonitor.hpp"
#include "UdpSocket.hpp"
#include "EntityManager.hpp"

namespace RType
{
    class NetworkSystem
    {
    public:
        NetworkSystem
                (EntityManager *em, std::string const& = defaultAddr, short
                int = defaultPortTCP);
        virtual ~NetworkSystem();

    public:
        void        process();
        std::string toString() const;


    public:
        static const short int   defaultPortTCP;
        static const std::string defaultAddr;
        static const size_t      buffLen;

    private:
        EntityManager *_entityManager;
        SocketMonitor& _monitor;
        TcpConnector _connector;
    };
}

#endif //RTYPE_SERVER_CLIENTNETWORK_HPP