#include <memory>
#include "CommandFactory.hpp"
#include "UsernameCommand.hpp"

namespace RType
{
    namespace Command
    {
        Factory::Factory()
        {
            learn(std::make_unique<Command::Username>());
        }

        Factory::~Factory()
        {
        }
    }
}
