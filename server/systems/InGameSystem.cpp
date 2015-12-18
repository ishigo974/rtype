#include <iostream>
#include "InGameSystem.hpp"
#include "ComponentsMasks.hpp"

namespace RType
{
    namespace System
    {
        /*
        ** Static variables
        */
        const size_t    InGame::bufferSize  = 65000;

        /*
        ** Constructor/Destructor
        */
        InGame::InGame(short int port) : _socket(port)
        {
        }

        InGame::~InGame()
        {
        }

        /*
        ** Public member functions
        */
        void            InGame::update()
        {
            Buffer      buffer;
            std::string addr;

            _socket.receiveFrom(buffer, bufferSize, addr);
            _book[addr].append(buffer);
        }

        void            InGame::processEntity(ECS::Entity& /*e*/)
        {
        }

        ECS::ComponentMask   InGame::getMask() const
        {
            return Component::MASK_NETWORKUDP;
        }

        std::string     InGame::getName() const
        {
            return "InGameSystem";
        }

        bool            InGame::shouldAutoUpdate() const
        {
            return false;
        }

        bool            InGame::shouldAutoProcess() const
        {
            return true;
        }

        std::string     InGame::toString() const
        {
            return "System::InGame {}\n";
        }
    }
}
