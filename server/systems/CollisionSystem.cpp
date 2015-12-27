#include <iostream>
#include "CollisionSystem.hpp"
#include "PositionComponent.hpp"
#include "ShipComponent.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkUDP.hpp"
#include "EntityManager.hpp"
#include "MapParser.hpp"
#include "ColliderComponent.hpp"
#include "Server.hpp"
#include "MobComponent.hpp"

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
        Collision::Collision()
        {
        }

        Collision::~Collision()
        {
        }

        /*
        ** Public member functions
        */
        void            Collision::update()
        {
            ECS::EntityCollection   entities =
                ECS::EntityManager::getInstance()
                    .getByMask(Component::MASK_COLLIDER);

            for (auto& e: entities)
            {
                Component::Collider*    src =
                    e->getComponent<Component::Collider>();

                for (auto& f: entities)
                {
                    Component::Collider*    dest =
                        f->getComponent<Component::Collider>();

                    if (src != dest && src->intersects(*dest))
                    {
                        if ((e->getComponentMask() & Component::MASK_SHIP) ==
                            Component::MASK_SHIP)
                            e->getComponent<Component::Ship>()->collide(*f);
                        else if ((e->getComponentMask() & Component::MASK_MOB) ==
                            Component::MASK_MOB)
                            e->getComponent<Component::Mob>()->collide(*f);
                        else if ((e->getComponentMask() & Component::MASK_SHOT)
                                    == Component::MASK_SHOT)
                            e->getComponent<Component::Shot>()->collide(*f);
                    }
                }
            }
        }

        void            Collision::processEntity(ECS::Entity&)
        {
        }

        ECS::ComponentMask   Collision::getMask() const
        {
            return Component::MASK_COLLIDER | Component::MASK_POSITION;
        }

        std::string     Collision::getName() const
        {
            return "CollisionSystem";
        }

        bool            Collision::shouldAutoUpdate() const
        {
            return true;
        }

        bool            Collision::shouldAutoProcess() const
        {
            return false;
        }

        std::string     Collision::toString() const
        {
            return "System::Collision {}\n";
        }
    }
}
