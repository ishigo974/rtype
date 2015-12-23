#include "GameComponent.hpp"
#include "ComponentsMasks.hpp"
#include "EntityManager.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "ShipComponent.hpp"
#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"


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
        }

        Map::Parser::Map&       Game::retrieveMap()
        {
            return _map;
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
