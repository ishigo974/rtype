#include <memory>
#include "CommandEventFactory.hpp"
#include "MoveCommand.hpp"
#include "ShotCommand.hpp"

namespace RType
{
    namespace Command
    {
        EventFactory::EventFactory()
        {
            learn(std::make_unique<Command::Move>());
            learn(std::make_unique<Command::Shot>());
        }

        EventFactory::~EventFactory()
        {
        }
    }
}
