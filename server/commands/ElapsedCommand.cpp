#include <iostream>
#include <stdexcept>
#include "EntityManager.hpp"
#include "ElapsedCommand.hpp"
#include "RoomComponent.hpp"
#include "PlayerComponent.hpp"
#include "ShipComponent.hpp"
#include "GameComponent.hpp"
#include "InGameEvent.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructor/Destructor
        */
        Elapsed::Elapsed() : _elapsedTime(0)
        {
        }

        Elapsed::~Elapsed()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Elapsed::Elapsed(Elapsed const& other) :
            Event(other), _elapsedTime(other._elapsedTime)
        {
        }

        Elapsed&    Elapsed::operator=(Elapsed const& other)
        {
            if (this != &other)
            {
                Event::operator=(other);
                _elapsedTime = other._elapsedTime;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void        Elapsed::initFromEvent(InGameEvent const& event)
        {
            _elapsedTime = event.get<double>("elapsed_time");
        }

        Event*      Elapsed::clone() const
        {
            return new Elapsed(*this);
        }

        void        Elapsed::execute()
        {
            Component::Player*  player =
                _entity->getComponent<Component::Player>();
            Component::Ship*    ship =
                _entity->getComponent<Component::Ship>();
            Component::Room*    room;
            Component::Game*    game;

            if (player == nullptr || ship == nullptr
                || (room = player->getRoom()) == nullptr
                || (game = ECS::EntityManager::getInstance()
                        .getByCmpnt(room)
                        .getComponent<Component::Game>()) == nullptr)
                throw std::runtime_error("Entity does not have a "
                                         "player/ship/room component");
            ship->setElapsedTime(_elapsedTime);
            game->updateElapsedTime();
        }

        void        Elapsed::undo()
        {
        }

        std::string Elapsed::getName() const
        {
            return "ElapsedCommand";
        }
    }
}
