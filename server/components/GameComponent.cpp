#include "GameComponent.hpp"
#include "ComponentsMasks.hpp"
#include "EntityManager.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "ShipComponent.hpp"
#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"
#include "MapBoundaries.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Game::mask  = Component::MASK_GAME;

        /*
        ** Constructor/Destructor
        */
        Game::Game() : _chrono(), _mobs(), _room(nullptr), _map()
        {
        }

        Game::~Game()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Game::Game(Game const& other) :
            _chrono(other._chrono), _mobs(other._mobs),
            _room(other._room), _map(other._map)
        {
        }

        Game&           Game::operator=(Game const& other)
        {
            if (this != &other)
            {
                _chrono = other._chrono;
                _mobs = other._mobs;
                _room = other._room;
                _map = other._map;
            }
            return *this;
        }

        /*
        ** Public member functions
        */

        void                Game::update()
        {
            auto it = _mobs.begin();

            while (it != _mobs.end())
            {
                ECS::Entity&            e =
                    ECS::EntityManager::getInstance().getByCmpnt(*it);
                Component::Position*    pos =
                    e.getComponent<Component::Position>();

                if (pos->getX() <= 0 || pos->getX() >= Map::width
                    || pos->getY() <= 0 || pos->getY() >= Map::height)
                {
                    it = _mobs.erase(it);
                    ECS::EntityManager::getInstance().destroy(e);
                    continue ;
                }
                else
                    (*it)->move(0.2); // TODO elapsedTime
                ++it;
            }
        }

        Map::Parser::Map&       Game::retrieveMap()
        {
            return _map;
        }

        void                    Game::addMob(Component::Mob* mob)
        {
            _mobs.push_back(mob);
            std::cout << "mob spawned type " << mob->getId() << std::endl;
        }

        void                Game::start(Map::Parser::Map const& map)
        {
            _map = map;
            _room = ECS::EntityManager::getInstance()
                        .getByCmpnt(this)
                        .getComponent<Component::Room>();
            for (auto& entry: *_room)
            {
                ECS::Entity*            user = entry.second.first;
                Component::NetworkTCP*  tcp =
                    user->getComponent<Component::NetworkTCP>();

                user->addComponent(std::make_unique<Component::NetworkUDP>(
                        tcp->getIpAddr())
                    );
                user->addComponent(std::make_unique<Component::Position>(
                            Room::defaultPositions.at(entry.first)
                    ));
                user->addComponent(std::make_unique<Component::Ship>());
            }
            _chrono.start();
        }

        Time::HRChrono const&   Game::getChrono() const
        {
            return _chrono;
        }

        std::string         Game::getName() const
        {
            return "GameComponent";
        }

        ECS::ComponentMask  Game::getMask() const
        {
            return mask;
        }

        ECS::IComponent*    Game::clone() const
        {
            return new Game(*this);
        }

        void                Game::clear()
        {
        }

        std::string         Game::toString() const
        {
            return ""; // TODO
        }
    }
}
