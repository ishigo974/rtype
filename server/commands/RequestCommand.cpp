#include "RequestCommand.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructors/Destructor
        */
        Request::Request() : _entity(nullptr), _system(nullptr)
        {
        }

        Request::Request(ECS::Entity* entity) :
            _entity(entity), _system(nullptr)
        {
        }

        Request::~Request()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Request::Request(Request const& other) :
            _entity(other._entity)
        {
        }

        Request&        Request::operator=(Request const& other)
        {
            if (this != &other)
                _entity = other._entity;
            return *this;
        }

        /*
        ** Public member functions
        */
        void            Request::setEntity(ECS::Entity& entity)
        {
            _entity = &entity;
        }

        std::string     Request::toString() const
        {
            return getName();
        }
    }
}
