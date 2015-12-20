//
// Created by Denis Le Borgne on 18/12/2015.
//

#include "IncompleteRequest.hpp"
#include "UDPSystem.hpp"

namespace RType
{

    const short       UDPSystem::defaultPortUDP = 6668;
    const size_t      UDPSystem::buffLen        = 1024;

    UDPSystem::UDPSystem(EntityManager *em, short udp)
            : _entityManager(em), _socket(udp)
    {
        _socket.bind();
    }

    UDPSystem::~UDPSystem()
    { }

    void UDPSystem::process()
    {
        NetworkUDP            *netUDP;
        std::vector<Object *> components;
        Buffer                receive;
        std::string           addr;

        components = _entityManager->getByMask(ComponentMask::UDPMask);
        netUDP     = static_cast<GameObject *>(components[0])
                ->getComponent<NetworkUDP>();
        try
        {
            _socket.receiveFrom(receive, buffLen, addr);
        }
        catch (std::runtime_error const&)
        {
            _socket.close();
            //TODO Send UI disconnection
        }
        netUDP->receive(receive);
        try
        {
            _socket.sendTo(netUDP->toSend(), NetworkSystem::defaultAddr);
        }
        catch (std::runtime_error const&)
        { }
    }

    std::string UDPSystem::toString() const
    {
        std::ostringstream ss;

        ss << "UDPSystem {"
        << "\n\t Connector : " << this->_socket.toString()
        << "\n}" << std::endl;

        return ss.str();
    }
}
