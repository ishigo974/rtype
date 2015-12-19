//
// Created by Denis Le Borgne on 18/12/2015.
//

#ifndef RTYPE_SERVER_CLIENTNETWORK_HPP
#define RTYPE_SERVER_CLIENTNETWORK_HPP

#include "NetworkTCP.hpp"
#include "../../core/EntityManager.hpp"

namespace RType
{
    class NetworkSystem
    {
    public:
        NetworkSystem
                (EntityManager *em, std::string const& = defaultAddr, short
                int = defaultPortTCP, short int = defaultPortUDP);
        virtual ~NetworkSystem();

    public:
        void        process();
        void        pushRequest(Request const&);
        void        update();
        Request     popRequest();
        bool        pendingRequests() const;
        void        connect();
        bool        isConnected() const;
        std::string toString() const;
        void        buildRequest();
        void        disconnection();

    protected:
        void init();

    public:
        static const short int   defaultPortUDP;
        static const short int   defaultPortTCP;
        static const std::string defaultAddr;

    private:
        EntityManager *_entityManager;
        SocketMonitor& _monitor;
        TcpConnector _connector;
    };
}

#endif //RTYPE_SERVER_CLIENTNETWORK_HPP