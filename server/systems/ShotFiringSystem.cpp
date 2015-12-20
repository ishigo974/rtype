#include <iostream>
#include "ShotFiringSystem.hpp"
#include "PositionComponent.hpp"
#include "ShipComponent.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkUDP.hpp"
#include "EntityManager.hpp"

namespace RType
{
    namespace System
    {
        /*
        ** Static variables
        */
        /*
        ** Constructor/Destructor
        */
        ShotFiring::ShotFiring()
        {
        }

        ShotFiring::~ShotFiring()
        {
        }

        /*
        ** Public member functions
        */
        void            ShotFiring::update()
        {
        }

        void            ShotFiring::processEntity(ECS::Entity& e)
        {
            Component::Position*    pos =
                e.getComponent<Component::Position>();
            Component::Ship*        ship =
                e.getComponent<Component::Ship>();

            if (pos == nullptr || ship == nullptr)
                throw std::runtime_error("Entity does not have a "
                                         "Ship/Position component");
            if (ship->isFiring()/* && getElapsedTime() - lastTime > minDelay*/) // TODO
            {
                ECS::Entity&            shot = ECS::EntityManager::getInstance()
                    .create(Component::MASK_POSITION);
                Component::Position*    shotPos =
                    shot.getComponent<Component::Position>();

                shot.addComponent(
                    std::make_unique<Component::Shot>(ship->getShotType(), &e));
                *shotPos = *pos;
                // reset lastTime
            }
        }

        ECS::ComponentMask   ShotFiring::getMask() const
        {
            return Component::MASK_SHIP | Component::MASK_POSITION;
        }

        std::string     ShotFiring::getName() const
        {
            return "ShotFiringSystem";
        }

        bool            ShotFiring::shouldAutoUpdate() const
        {
            return true;
        }

        bool            ShotFiring::shouldAutoProcess() const
        {
            return true;
        }

        std::string     ShotFiring::toString() const
        {
            return "System::ShotFiring {}\n";
        }
    }
}
