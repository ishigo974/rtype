#include <memory>
#include "CommandEventFactory.hpp"
#include "MoveCommand.hpp"

namespace RType
{
    namespace Command
    {
        EventFactory::EventFactory()
        {
            learn(std::make_unique<Command::Move>());
        }

        EventFactory::~EventFactory()
        {
        }
    }
}
