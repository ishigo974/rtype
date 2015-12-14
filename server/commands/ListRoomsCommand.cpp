#include <iostream>
#include "ListRoomsCommand.hpp"
#include "ComponentsMasks.hpp"
#include "RoomComponent.hpp"
#include "NetworkTCP.hpp"
#include "Server.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructor/Destructor
        */
        ListRooms::ListRooms()
        {
        }

        ListRooms::~ListRooms()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        ListRooms::ListRooms(ListRooms const& other) :
            Command::Request(other), _rooms(other._rooms)
        {
        }

        ListRooms&  ListRooms::operator=(ListRooms const& other)
        {
            if (this != &other)
            {
                Command::Request::operator=(other);
                _rooms = other._rooms;
            }
            return *this;
        }


        /*
        ** Public member functions
        */
        void        ListRooms::initFromRequest(RType::Request const&,
                                                ECS::ASystem* system)
        {
            System::Lobby*      lobby;

            if ((lobby = dynamic_cast<System::Lobby*>(system)) == nullptr)
                throw std::runtime_error("Can't initialize command: \
expected LobbySystem"); // TODO
            _rooms = &lobby->getRooms();
        }

        void        ListRooms::execute()
        {
            Component::NetworkTCP*  network;
            Buffer                  response;
            Buffer                  data;

            response.append<uint16_t>(RType::Request::SE_LISTROOMS);
            for (auto& entry: *_rooms)
            {
                Component::Room*  room =
                    entry.second
                        ->getComponent<Component::Room>(Component::MASK_ROOM);

                if (room == nullptr)
                    throw std::runtime_error("Can't execute command: \
entity does not have a room component");
                data.append<uint32_t>(entry.first);
                data.append<uint32_t>(room->getRoomName().size());
                data.append<std::string>(room->getRoomName());
                data.append<uint8_t>(room->size());
            }
            response.append<uint32_t>(data.size());
            response.append(data);
            if ((network = _entity->getComponent<Component::NetworkTCP>(
                Component::MASK_NETWORKTCP)) == nullptr)
                throw std::runtime_error("Can't execute command: \
entity does not have a NetworkTCP component");
            network->send(response);
        }

        void        ListRooms::undo()
        {
        }

        Request*    ListRooms::clone() const
        {
            return new ListRooms(*this);
        }

        std::string ListRooms::getName() const
        {
            return "ListRoomsCommand";
        }
    }
}
