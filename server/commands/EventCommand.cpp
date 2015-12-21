#include "EventCommand.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructor/Destructor
        */
        Event::Event()
        {
        }

        Event::Event(ECS::Entity* entity) : _entity(entity)
        {
        }

        Event::~Event()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Event::Event(Event const& other) : _entity(other._entity)
        {
        }

        Event&      Event::operator=(Event const& other)
        {
            if (this != &other)
                _entity = other._entity;
            return *this;
        }

        /*
        ** Public member functions
        */
        void        Event::setEntity(ECS::Entity& entity)
        {
            _entity = &entity;
        }

        std::string Event::toString() const
        {
            return getName();
        }
    }
}
