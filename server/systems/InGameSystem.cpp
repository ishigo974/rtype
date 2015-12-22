#include <iostream>
#include "InGameSystem.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkUDP.hpp"

namespace RType
{
    namespace System
    {
        /*
        ** Static variables
        */
        const size_t                InGame::bufferSize = 65000;
        const InGame::EventCmdMap   InGame::cmdsNames =
                                            {
                                                    {InGameEvent::CL_PLAYERUP,   "MoveCommand"},
                                                    {InGameEvent::CL_PLAYERDOWN, "MoveCommand"},
                                                    {InGameEvent::CL_PLAYERLEFT, "MoveCommand"},
                                                    {InGameEvent::CL_PLAYERRIGHT, "MoveCommand"},
                                                    {InGameEvent::CL_SHOTSTART,  "ShotCommand"},
                                                    {InGameEvent::CL_SHOTSTOP,   "ShotCommand"}
                                            };

        /*
        ** Constructor/Destructor
        */
        InGame::InGame(short int port) : _socket(port)
        {
            _socket.bind();
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

            if (_socket.receiveFrom(buffer, bufferSize, addr) > 0)
                _book[addr].append(buffer);
        }

        void            InGame::processEntity(ECS::Entity& e)
        {
            IpBufferBook::iterator it;
            Component::NetworkUDP *udp = e.getComponent<
                                                  Component::NetworkUDP>();

            if (udp == nullptr)
                throw std::runtime_error("InGameSystem: Entity has no "
                                                 "NetworkUDP component");
            if ((it = _book.find(udp->getIpAddr())) != _book.end())
            {
                udp->pushReceived(it->second);
                _book.erase(it);
            }
            while (udp->isEvent())
            {
                InGameEvent                     event = udp->popEvent();
                std::unique_ptr<Command::Event> cmd   = _factory.generate(
                                                                cmdsNames.at(
                                                                        static_cast<InGameEvent::Code>(event
                                                                                .getCode()))
                                                        );

                cmd->setEntity(e);
                cmd->initFromEvent(event);
                cmd->execute();
                std::cout << event << std::endl;
            }
            if (udp->isToSend())
                _socket.sendTo(udp->popToSend(), udp->getIpAddr());
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
