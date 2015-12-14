#include <iostream>
#include <sstream>
#include "LobbySystem.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkTCP.hpp"
#include "Request.hpp"
#include "ValueError.hpp"
#include "Server.hpp"
#include "CommandFactory.hpp"
#include "Request.hpp"
#include "RoomComponent.hpp"

namespace RType
{
    namespace System
    {
        /*
        ** Static variables
        */
        const Lobby::RequestCmdMap      Lobby::cmdsNames    = {
            { Request::LR_LISTROOMS,    "ListRoomsCommand"  },
            { Request::LR_CREATEROOM,   "CreateRoomCommand" },
            { Request::LR_QUITROOM,     "QuitRoomCommand"   },
            { Request::LR_USERNAME,     "UsernameCommand"   },
            { Request::LR_READY,        "ReadyCommand"      },
            { Request::LR_NOTREADY,     "NotReadyCommand"   },
            { Request::LR_JOINROOM,     "JoinRoomCommand"   }
        };

        /*
        ** Constructor/Destructor
        */
        Lobby::Lobby()
        {
        }

        Lobby::~Lobby()
        {
        }

        /*
        ** Public member functions
        */
        void                Lobby::update()
        {
            auto it = _rooms.begin();

            while (it != _rooms.end())
            {
                Component::Room* room = it->second
                    ->getComponent<Component::Room>(Component::MASK_ROOM);

                if (room->size() == 0)
                {
                    ECS::EntityManager::getInstance().destroy(*it->second);
                    _rooms.erase(it);
                    it = _rooms.begin();
                }
                else
                    ++it;
            }
        }

        void                Lobby::processEntity(ECS::Entity& e)
        {
            Component::NetworkTCP*  network = e
                .getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP);

            while (network->isRequest())
            {
                try {
                    RType::Request  request = network->popRequest();

                    Lobby::buildCommand(request, e)->execute();
                    Server::display("Received request " +
                        std::to_string(request.getCode()) + " from " +
                        network->repr());
                } catch (Exception::ValueError const& e) {
                    Server::display(std::string(e.what()), true);
                } catch (std::out_of_range const&) {
                    Server::display("Can't build command from \
request, ignored (" + network->repr() + ")", true);
                }
            }
        }

        void                Lobby::addRoom(ECS::Entity& room)
        {
            _rooms.insert(std::make_pair(room.getId(), &room));
        }

        Component::Room*    Lobby::getRoom(unsigned int id) const
        {
            auto it = _rooms.find(id);

            if (it == _rooms.end())
                return nullptr;
            return it->second
                        ->getComponent<Component::Room>(Component::MASK_ROOM);
        }

        ECS::ComponentMask  Lobby::getMask() const
        {
            return Component::MASK_NETWORKTCP;
        }

        std::string         Lobby::getName() const
        {
            return "LobbySystem";
        }

        Lobby::RoomsMap const&     Lobby::getRooms() const
        {
            return _rooms;
        }

        std::string         Lobby::toString() const
        {
            return "LobbySystem { mask: " + std::to_string(getMask()) + "}";
        }

        /*
        ** Protected member functions
        */
        Command::Request*   Lobby::buildCommand(Request const& request,
                                                ECS::Entity& entity)
        {
            Command::Request*       cmd = _factory.generate(cmdsNames.at(
                        static_cast<Request::LobbyRequest>(request.getCode())
                    ));

            if (cmd == nullptr)
                throw Exception::ValueError("No command corresponding \
to request code " + std::to_string(request.getCode()));
            cmd->setEntity(entity);
            cmd->initFromRequest(request, this);
            return cmd;
        }
    }
}