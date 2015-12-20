//
// Created by Denis Le Borgne on 20/12/2015.
//

#ifndef RTYPE_UDPSYSTEM_HPP
#define RTYPE_UDPSYSTEM_HPP

#include "NetworkUDP.hpp"
#include "UdpSocket.hpp"
#include "SocketMonitor.hpp"
#include "EntityManager.hpp"

namespace RType
{
    class UDPSystem
    {
    public:
        UDPSystem(EntityManager *em, std::string const& addr =
        NetworkSystem::defaultAddr, short int = defaultPortUDP);
        virtual ~UDPSystem();

    public:
        void        process();
        std::string toString() const;


    public:
        static const short int defaultPortUDP;
        static const size_t    buffLen;

    private:
        EntityManager *_entityManager;
        std::string   _addr;
        UdpSocket     _socket;
    };
}
#endif //RTYPE_UDPSYSTEM_HPP
