//
// Created by Denis Le Borgne on 18/12/2015.
//

#include "IncompleteRequest.hpp"
#include "SocketMonitor.hpp"
#include "NetworkSystem.hpp"

namespace RType
{

    const short NetworkSystem::defaultPortUDP = 9999;
    const short NetworkSystem::defaultPortTCP = 6667;
    const std::string NetworkSystem::defaultAddr = "127.0.0.1";
    const size_t      NetworkSystem::buffLen = 1024;

    NetworkSystem::NetworkSystem(EntityManager *em, std::string const& addr,
                                 short tcp, short)
            : _entityManager(em), _monitor(SocketMonitor::getInstance()),
              _connector(addr, tcp)
    {
        init();
    }

    NetworkSystem::~NetworkSystem()
    { }

    void NetworkSystem::process()
    {
        NetworkTCP            *netTcp;
        std::vector<Object *> components;
        Buffer                receive;

        components = _entityManager->getByMask(ComponentMask::NetworkMask);
        netTcp     = static_cast<GameObject *>(components[0])->getComponent<NetworkTCP>();

        try
        {
            _monitor.update();
        }
        catch (...)
        {

        }
        if (_monitor.isReadable(&_connector))
        {
            _connector.receive(receive, buffLen);
            Request               tmp(receive);
            netTcp->receive(tmp.toBuffer());
        }
        if (_monitor.isWritable(&_connector))
            _connector.send(netTcp->toSend());
    }

    void NetworkSystem::init()
    {
        _connector.connect();
        SocketMonitor::getInstance().registerSocket(&_connector);
    }

    std::string NetworkSystem::toString() const
    {
        std::ostringstream ss;

        ss << "NetworkSystem {"
        << "\n\t Connector : " << this->_connector.toString()
        << "\n}" << std::endl;

        return ss.str();
    }

    void NetworkSystem::buildRequest()
    {
    }

    Request NetworkSystem::popRequest()
    {
    }

    bool NetworkSystem::pendingRequests() const
    {
    }

    void NetworkSystem::disconnection()
    {

    }

    void NetworkSystem::connect()
    {
    }

    bool NetworkSystem::isConnected() const
    {
    }
}
