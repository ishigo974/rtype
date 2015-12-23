#include <iostream>
#include "GameSystem.hpp"
#include "PositionComponent.hpp"
#include "ShipComponent.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkUDP.hpp"
#include "EntityManager.hpp"
#include "MapParser.hpp"
#include "GameComponent.hpp"

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
        Game::Game(MobType::Collection const& mobsTypes) : _mobTypes()
        {
            for (auto& mobType: mobsTypes)
            {
                _mobTypes[mobType->getId()] =
                    std::unique_ptr<MobType::IMobType>(mobType);
            }
        }

        Game::~Game()
        {
        }

        /*
        ** Public member functions
        */
        void            Game::update()
        {
        }

        void            Game::processEntity(ECS::Entity& e)
        {
            Component::Game*    game = e.getComponent<Component::Game>();
            Map::Parser::Map&   map = game->retrieveMap();

            for (auto it = map.second.begin(); it != map.second.end(); ++it)
            {
                if ((it->first * 1000000) <= game->getChrono().getElapsedTime())
                {
                    // GameObject *first = _em->createEntity<GameObject>("LePremier", 0);

                    // _em->attachComponent<SpriteRenderer>(first, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
                    // _em->attachComponent<Mob>(first, "SR compo", _mobTypes->begin()->second.get());
                    // _em->attachComponent<Collider>(first, "SR compo", 32, 21);
                    // first->getComponent<Transform>()->getPosition().setX(it->second.x);
                    // first->getComponent<Transform>()->getPosition().setY(it->second.y);
                    std::cout << "mob" << std::endl;
                    if ((it = map.second.erase(it)) == map.second.end())
                        break ;
                }
                else
                    break ;
            }
            if (map.second.empty())
                std::cout << "end of map" << std::endl; // TODO end of game
        }

        Game::MobTypeMap const&   Game::getMobsTypes() const
        {
            return _mobTypes;
        }

        ECS::ComponentMask   Game::getMask() const
        {
            return Component::MASK_GAME;
        }

        std::string     Game::getName() const
        {
            return "GameSystem";
        }

        bool            Game::shouldAutoUpdate() const
        {
            return true;
        }

        bool            Game::shouldAutoProcess() const
        {
            return true;
        }

        std::string     Game::toString() const
        {
            return "System::Game {}\n";
        }
    }
}
