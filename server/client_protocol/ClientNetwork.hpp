//
// Created by Denis Le Borgne on 18/12/2015.
//

#ifndef RTYPE_SERVER_CLIENTNETWORK_HPP
#define RTYPE_SERVER_CLIENTNETWORK_HPP

#include "IStringable.hpp"
#include "NetworkTCP.hpp"

namespace RType
{
    class ClientNetwork
    {
    public:
        ClientNetwork
                (std::string const& = defaultAddr, short int = defaultPortTCP,
                 short int = defaultPortUDP);
        virtual ~ClientNetwork();

    public:
        void initTCPConnection();
        void initUDPConnection();

    public:
        static const short int   defaultPortUDP;
        static const short int   defaultPortTCP;
        static const std::string defaultAddr;

    private:
        SocketMonitor& _monitor;
        NetworkTCP _tcpManager;
    };
}

#endif //RTYPE_SERVER_CLIENTNETWORK_HPP
