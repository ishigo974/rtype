#include <iostream>
#include <sstream>
#include "LobbySystem.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkTCP.hpp"
#include "Request.hpp"

namespace RType
{
    namespace System
    {
        /*
        ** Constructor/Destructor
        */
        Lobby::Lobby()
        {
        }

        Lobby::~Lobby()
        {
        }

        /*
        ** Public member functions
        */
        void                Lobby::processEntity(ECS::Entity& e)
        {
            Component::NetworkTCP*  network = e
                .getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP);

            while (network->isRequest())
            {
                Request     request = network->popRequest();

                std::cout << request << std::endl; // todo
            }
        }

        ECS::ComponentMask  Lobby::getMask() const
        {
            return Component::MASK_NETWORKTCP;
        }

        std::string         Lobby::getName() const
        {
            return "LobbySystem";
        }

        std::string         Lobby::toString() const
        {
            return "LobbySystem { mask: " + std::to_string(getMask()) + "}";
        }

        /*
        ** Protected member functions
        */
        void                Lobby::handleRequest()
        {
        }
    }
}
