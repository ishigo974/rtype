#include <iostream>
#include "MoveCommand.hpp"

namespace RType
{
    namespace Command
    {
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
            std::cout << "move to " << static_cast<int>(_direction) << std::endl;
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
