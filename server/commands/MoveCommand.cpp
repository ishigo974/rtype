#include <iostream>
#include <stdexcept>
#include "MoveCommand.hpp"
#include "RoomComponent.hpp"
#include "PositionComponent.hpp"
#include "PlayerComponent.hpp"
#include "InGameEvent.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Static variables
        */
        const Move::DirCodeMatch   Move::dirCodeMatches  =
        {
            { UP,     InGameEvent::SE_PLAYERUP    },
            { DOWN,   InGameEvent::SE_PLAYERDOWN  },
            { LEFT,   InGameEvent::SE_PLAYERLEFT  },
            { RIGHT,  InGameEvent::SE_PLAYERRIGHT }
        };

        /*
        ** Constructor/Destructor
        */
        Move::Move() : _direction(Move::NONE)
        {
        }

        Move::~Move()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Move::Move(Move const& other) :
            Event(other), _direction(other._direction)
        {
        }

        Move&       Move::operator=(Move const& other)
        {
            if (this != &other)
            {
                Event::operator=(other);
                _direction = other._direction;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void        Move::initFromEvent(InGameEvent const& event)
        {
            switch (event.getCode())
            {
                case InGameEvent::CL_PLAYERUP:
                    _direction = UP;
                    break ;
                case InGameEvent::CL_PLAYERDOWN:
                    _direction = DOWN;
                    break ;
                case InGameEvent::CL_PLAYERLEFT:
                    _direction = LEFT;
                    break ;
                case InGameEvent::CL_PLAYERRIGHT:
                    _direction = RIGHT;
                    break ;
                default:
                    throw std::runtime_error("Can't init MoveCommand: "
                                             "wrong event");
                    break ;
            }
            _time = event.get<uint32_t>("time");
        }

        Event*      Move::clone() const
        {
            return new Move(*this);
        }

        void        Move::execute()
        {
            static const float      speed = 10.0f; // TODO
            Component::Position*    pos =
                _entity->getComponent<Component::Position>();
            Component::Player*      player =
                _entity->getComponent<Component::Player>();
            Component::Room*        room;
            InGameEvent             event;

            if (_direction == NONE)
                return ;
            if (pos == nullptr || player == nullptr
                || ((room = player->getRoom()) == nullptr))
                throw std::runtime_error("Entity does not have a "
                                         "position/room component");
            switch (_direction)
            {
                case NONE:
                    break ;
                case UP:
                    pos->setY(pos->getY() < static_cast<unsigned int>(speed) ? 0 : pos->getY() - static_cast<unsigned int>(speed));
                    break ;
                case DOWN:
                    pos->setY(pos->getY() + static_cast<unsigned int>(speed) > 720 ? 720 : pos->getY() + static_cast<unsigned int>(speed)); // TODO
                    break ;
                case LEFT:
                    pos->setX(pos->getX() < static_cast<unsigned int>(speed) ? 0 : pos->getX() - static_cast<unsigned int>(speed));
                    break ;
                case RIGHT:
                    pos->setX(pos->getX() + static_cast<unsigned int>(speed) > 1280 ? 1280 : pos->getX() + static_cast<unsigned int>(speed)); // TODO
                    break ;
            }
            event.setCode(dirCodeMatches.at(_direction));
            event.push<uint8_t>("player_id", room->getPlayerId(*_entity));
            event.push<uint32_t>("time", _time);
            room->broadcastUDP(event.toBuffer(), _entity);
        }

        void        Move::undo()
        {
        }

        std::string Move::getName() const
        {
            return "MoveCommand";
        }
    }
}
