#include "GameComponent.hpp"
#include "ComponentsMasks.hpp"
#include "EntityManager.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "ShipComponent.hpp"
#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"
#include "GameConfig.hpp"

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
        Game::Game() : _chrono(), _room(nullptr), _map(), _lag(0)
        {
        }

        Game::~Game()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Game::Game(Game const& other) :
            _chrono(other._chrono), _room(other._room),
            _map(other._map), _clock(other._clock), _lag(other._lag)
        {
        }

        Game&           Game::operator=(Game const& other)
        {
            if (this != &other)
            {
                _chrono = other._chrono;
                _room = other._room;
                _map = other._map;
                _clock = other._clock;
                _lag = other._lag;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void                Game::update()
        {
            _lag = (_clock.updateElapsedTime() * 100000); // tmp, elapsedtime trop petit
        }

        Map::Parser::Map&   Game::retrieveMap()
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

        double              Game::getLastElapsed() const
        {
            return _lag;
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
            _chrono = Time::HRChrono();
            _room = nullptr;
            _map.first.clear();
            _map.second.clear();
            _clock = Time::GameClock();
            _lag = 0;
        }

        std::string         Game::toString() const
        {
            return "Component::Game {}";
        }
    }
}
