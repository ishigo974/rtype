#include <memory>
#include "CommandEventFactory.hpp"
#include "MoveCommand.hpp"
#include "ShotCommand.hpp"
#include "ElapsedCommand.hpp"

namespace RType
{
    namespace Command
    {
        EventFactory::EventFactory()
        {
            learn(std::make_unique<Command::Move>());
            learn(std::make_unique<Command::Shot>());
            learn(std::make_unique<Command::Elapsed>());
        }

        EventFactory::~EventFactory()
        {
        }
    }
}
