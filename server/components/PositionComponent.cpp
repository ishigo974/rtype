#include "PositionComponent.hpp"
#include "ComponentsMasks.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Position::mask  = Component::MASK_POSITION;

        /*
        ** Constructor/Destructor
        */
        Position::Position(unsigned int x, unsigned int y) : _x(x), _y(y)
        {
        }

        Position::~Position()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Position::Position(Position const& other) : _x(other._x), _y(other._y)
        {
        }

        Position&       Position::operator=(Position const& other)
        {
            if (this != &other)
            {
                _x = other._x;
                _y = other._y;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        unsigned int            Position::getX() const
        {
            return _x;
        }

        unsigned int            Position::getY() const
        {
            return _y;
        }

        void                    Position::setX(unsigned int x)
        {
            _x = x;
        }

        void                    Position::setY(unsigned int y)
        {
            _y = y;
        }

        std::string         Position::getName() const
        {
            return "PositionComponent";
        }

        ECS::ComponentMask  Position::getMask() const
        {
            return mask;
        }

        std::string         Position::toString() const
        {
            return "Component::Position {"
                   "\n\t_x: " + std::to_string(_x) +
                   "\n\t_y: " + std::to_string(_y) +
                   "\n}\n";
        }

        ECS::IComponent*    Position::clone() const
        {
            return new Position(*this);
        }

        void                Position::clear()
        {
            _x = 0;
            _y = 0;
        }
    }
}
