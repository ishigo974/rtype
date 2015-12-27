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
                throw std::runtime_error("Can't initialize command: "
                                         "expected LobbySystem");
            _rooms = &lobby->getRooms();
        }

        void        ListRooms::execute()
        {
            Component::NetworkTCP*  network;
            RType::Request          request(RType::Request::SE_LISTROOMS);
            Buffer                  data;

            for (auto& entry: *_rooms)
            {
                Component::Room*  room =
                    entry.second
                        ->getComponent<Component::Room>();

                if (room == nullptr)
                    throw std::runtime_error("Can't execute command: \
entity does not have a room component");
                if (room->isPlaying())
                    continue ;
                data.append<uint32_t>(entry.first);
                data.append<uint32_t>(room->getRoomName().size());
                data.append<std::string>(room->getRoomName());
                data.append<uint8_t>(room->size());
            }
            request.push<Buffer>("rooms", data);
            if ((network = _entity->getComponent<Component::NetworkTCP>())
                    == nullptr)
                throw std::runtime_error("Can't execute command: \
entity does not have a NetworkTCP component");
            network->send(request.toBuffer());
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
