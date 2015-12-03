#include "ACommand.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructors/Destructor
        */
        ACommand::ACommand() : _entity(nullptr)
        {
        }

        ACommand::ACommand(ECS::Entity* entity) : _entity(entity)
        {
        }

        ACommand::~ACommand()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        ACommand::ACommand(ACommand const& other) : _entity(other._entity)
        {
        }

        ACommand&       ACommand::operator=(ACommand const& other)
        {
            if (this != &other)
                _entity = other._entity;
            return *this;
        }
    }
}
