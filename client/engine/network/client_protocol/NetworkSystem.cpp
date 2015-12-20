//
// Created by Denis Le Borgne on 18/12/2015.
//

#include "IncompleteRequest.hpp"
#include "SocketMonitor.hpp"
#include "NetworkSystem.hpp"

namespace RType
{

    const short NetworkSystem::defaultPortTCP = 6667;
    const std::string NetworkSystem::defaultAddr = "127.0.0.1";
    const size_t      NetworkSystem::buffLen = 1024;

    NetworkSystem::NetworkSystem(EntityManager *em, std::string const& addr,
                                 short tcp)
            : _entityManager(em), _monitor(SocketMonitor::getInstance()),
              _connector(addr, tcp)
    {
        _connector.connect();
        SocketMonitor::getInstance().registerSocket(&_connector);
    }

    NetworkSystem::~NetworkSystem()
    {
        _connector.close();
    }

    void NetworkSystem::process()
    {
        NetworkTCP            *netTcp;
        std::vector<Object *> components;
        Buffer                receive;

        components = _entityManager->getByMask(ComponentMask::TCPMask);
        netTcp     = static_cast<GameObject *>(components[0])
                ->getComponent<NetworkTCP>();

        try
        {
            _monitor.update();
        }
        catch (std::runtime_error const&)
        {

        }
        if (_monitor.isReadable(&_connector))
        {
            try
            {
                _connector.receive(receive, buffLen);
            }
            catch (std::runtime_error const&)
            {
                _connector.close();
                _monitor.deleteSocket(&_connector);
                //TODO Send UI disconnection
            }
            netTcp->receive(receive);
        }
        if (_monitor.isWritable(&_connector))
            _connector.send(netTcp->toSend());
    }

    std::string NetworkSystem::toString() const
    {
        std::ostringstream ss;

        ss << "NetworkSystem {"
        << "\n\t Connector : " << this->_connector.toString()
        << "\n}" << std::endl;

        return ss.str();
    }
}
