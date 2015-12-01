#include <iostream>
#include "LobbySystem.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkTCP.hpp"

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
            Buffer          data = e
                .getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP)
                ->popData();

            std::cout << data.data() << std::endl;
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
    }
}
