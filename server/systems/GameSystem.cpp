#include <iostream>
#include "GameSystem.hpp"
#include "PositionComponent.hpp"
#include "ShipComponent.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkUDP.hpp"
#include "EntityManager.hpp"
#include "MapParser.hpp"
#include "GameComponent.hpp"
#include "Server.hpp"

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
            Component::Room*    room = e.getComponent<Component::Room>();
            Map::Parser::Map&   map = game->retrieveMap();

            if (map.second.empty())
                return ;
            for (auto it = map.second.begin(); it != map.second.end(); ++it)
            {
                if ((it->first * 1000000) <= game->getChrono().getElapsedTime())
                {
                    auto mobType = _mobTypes.find(it->second.id);

                    if (mobType == _mobTypes.end())
                    {
                        Server::display("Warning: No such mob type: "
                                        + std::to_string(it->second.id));
                        if ((it = map.second.erase(it)) == map.second.end())
                            break ;
                        continue ;
                    }
                    ECS::Entity&    eMob = ECS::EntityManager::getInstance()
                        .create(Component::MASK_MOB | Component::MASK_POSITION); // TODO add collider
                    Component::Mob* cMob = eMob.getComponent<Component::Mob>();
                    Component::Position*    cPos =
                        eMob.getComponent<Component::Position>();
                    InGameEvent             event(InGameEvent::SE_MOBSPAWNED);

                    cMob->init(mobType->second.get());
                    cPos->setX(it->second.x);
                    cPos->setX(it->second.y);
                    game->addMob(cMob);

                    event.push<uint8_t>("mob_id", cMob->getId());
                    event.push<uint32_t>("x", it->second.x);
                    event.push<uint32_t>("y", it->second.y);
                    event.push<uint32_t>("time",
                                         game->getChrono().getElapsedTime());
                    room->broadcastUDP(event.toBuffer());
                    if ((it = map.second.erase(it)) == map.second.end())
                        break ;
                }
                else
                    break ;
            }
            if (map.second.empty())
            {
                std::cout << "end of map" << std::endl; // TODO end of game
            }
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
