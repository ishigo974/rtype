//
// Created by Denis Le Borgne on 18/12/2015.
//

#include "SocketMonitor.hpp"
#include "NetworkSystem.hpp"

namespace RType
{

    const short NetworkSystem::defaultPortUDP = 9999;
    const short NetworkSystem::defaultPortTCP = 6667;
    const std::string NetworkSystem::defaultAddr = "127.0.0.1";

    NetworkSystem::NetworkSystem(EntityManager* em, std::string const& addr,
                                 short tcp, short)
            : _entityManager(em), _monitor(SocketMonitor::getInstance()),
                             _tcpManager(addr, tcp)
    {
        init();
    }

    NetworkSystem::~NetworkSystem()
    { }

    void NetworkSystem::process()
    {
        try
        {
            _monitor.update();
        } catch (...)
        {

        }
        _tcpManager.update();
    }

    void NetworkSystem::init()
    {
        _tcpManager.connect();
    }
}
