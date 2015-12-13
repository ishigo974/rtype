#include <memory>
#include "CommandFactory.hpp"
#include "UsernameCommand.hpp"
#include "CreateRoomCommand.hpp"
#include "ListRoomsCommand.hpp"
#include "QuitRoomCommand.hpp"
#include "ReadyCommand.hpp"
#include "NotReadyCommand.hpp"

namespace RType
{
    namespace Command
    {
        Factory::Factory()
        {
            learn(std::make_unique<Command::Username>());
            learn(std::make_unique<Command::CreateRoom>());
            learn(std::make_unique<Command::ListRooms>());
            learn(std::make_unique<Command::QuitRoom>());
            learn(std::make_unique<Command::Ready>());
            learn(std::make_unique<Command::NotReady>());
        }

        Factory::~Factory()
        {
        }
    }
}
