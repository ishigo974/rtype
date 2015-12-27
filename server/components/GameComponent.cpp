#include "GameComponent.hpp"
#include "ComponentsMasks.hpp"
#include "EntityManager.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "RoomComponent.hpp"
#include "ShipComponent.hpp"
#include "ColliderComponent.hpp"
#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"
#include "GameConfig.hpp"
#include "Server.hpp"

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
        Game::Game() :
            _chrono(), _room(nullptr), _map()
        {
        }

        Game::~Game()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Game::Game(Game const& other) :
            _chrono(other._chrono), _room(other._room), _map(other._map)
        {
        }

        Game&           Game::operator=(Game const& other)
        {
            if (this != &other)
            {
                _chrono = other._chrono;
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
            return ;
            bool            endGame(true);
            Buffer          score;

            for (auto& room: *_room)
            {
                Component::Ship*    ship =
                    room.second.first->getComponent<Component::Ship>();

                if (ship->getLives() > 0)
                    endGame = false;
                score.append<uint8_t>(room.first);
                score.append<uint32_t>(ship->getScore());
            }
            if (endGame)
            {
                Request     request(Request::SE_ENDOFGAME);

                std::cout << "lololol end !!!" << std::endl;
                request.push<Buffer>("scores", score);
                _room->broadcastTCP(request.toBuffer());
            }
        }

        Map::Parser::Map&   Game::retrieveMap()
        {
            return _map;
        }

        std::string const&  Game::getMapName() const
        {
            return _map.first;
        }

        Component::Room*    Game::getRoom() const
        {
            return _room;
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
                            Map::defaultPosX, Map::defaultPosY.at(entry.first)
                    ));
                user->addComponent(std::make_unique<Component::Ship>());
                user->addComponent(
                    std::make_unique<Component::Collider>(RType::Ship::width,
                                                      RType::Ship::height));
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
            _chrono = Time::HRChrono();
            _room = nullptr;
            _map.first.clear();
            _map.second.clear();
        }

        std::string         Game::toString() const
        {
            return "Component::Game {}";
        }
    }
}
