//
// Created by Denis Le Borgne on 18/12/2015.
//

#ifndef RTYPE_SERVER_CLIENTNETWORK_HPP
#define RTYPE_SERVER_CLIENTNETWORK_HPP

#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"
#include "SocketMonitor.hpp"
#include "UdpSocket.hpp"
#include "EntityManager.hpp"

namespace RType
{
    class NetworkSystem
    {
    public:
        NetworkSystem
                (EntityManager *em, std::string const& = defaultAddr,
                 short int = defaultPortTCP, short int udpPort = defaultPortUDP);
        virtual ~NetworkSystem();

    public:
        void        processTCP();
        void        processUDP();
        std::string toString() const;

    public:
        void        pushTCP(Request const& request);
        void        pushUDP(InGameEvent const& request);
        Request     popTCP();
        InGameEvent popUDP();

    public:
        size_t tcpSize() const;
        size_t udpSize() const;

    public:
        static const short int   defaultPortTCP;
        static const std::string defaultAddr;
        static const size_t      buffLen;
        static const short int   defaultPortUDP;

    private:
        EntityManager *_entityManager;
        SocketMonitor& _monitor;
        TcpConnector _connector;

        RType::NetworkTCP _tcpObj;
        RType::NetworkUDP _udpObj;
        UdpSocket         _udpSock;
        std::string       _addr;
    };
}

#endif //RTYPE_SERVER_CLIENTNETWORK_HPP