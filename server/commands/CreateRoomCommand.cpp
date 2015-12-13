#include "CreateRoomCommand.hpp"
#include "EntityManager.hpp"
#include "ComponentsMasks.hpp"
#include "RoomComponent.hpp"
#include "PlayerComponent.hpp"
#include "NetworkTCP.hpp"
#include "Server.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructor/Destructor
        */
        CreateRoom::CreateRoom() : _lobby(nullptr)
        {
        }

        CreateRoom::~CreateRoom()
        {
        }


        /*
        ** Copy constructor and assign operator
        */
        CreateRoom::CreateRoom(CreateRoom const& other) :
            Command::Request(other),
            _roomName(other._roomName), _lobby(other._lobby)
        {
        }

        CreateRoom&     CreateRoom::operator=(CreateRoom const& other)
        {
            if (this != &other)
            {
                Command::Request::operator=(other);
                _roomName = other._roomName;
                _lobby = other._lobby;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void        CreateRoom::initFromRequest(RType::Request const& request,
                                                ECS::ASystem* sys)
        {
            if ((_lobby = dynamic_cast<System::Lobby*>(sys)) == nullptr)
                throw std::runtime_error("Can't initialize command: \
expected LobbySystem"); // TODO
            _roomName = request.get<std::string>("room_name");
        }

        void        CreateRoom::execute()
        {
            ECS::Entity&            e =
                ECS::EntityManager::getInstance().create(Component::MASK_ROOM);
            Component::Room*        room =
                e.getComponent<Component::Room>(Component::MASK_ROOM);
            Component::Player*      player =
                _entity->getComponent<Component::Player>(Component::MASK_PLAYER);
            Component::NetworkTCP*  network =
                _entity->getComponent<Component::NetworkTCP>(
                    Component::MASK_NETWORKTCP);

            if (room == nullptr || player == nullptr || network == nullptr)
                throw std::runtime_error("Entity does not have a \
room/player/network component");
            // validation name TODO
            room->addPlayer(*_entity);
            room->setName(_roomName);
            _lobby->addRoom(e);
            player->setRoom(room);
            network->send(Server::responseOK);
        }

        void        CreateRoom::undo()
        {
        }

        Request*    CreateRoom::clone() const
        {
            return new CreateRoom(*this);
        }

        std::string CreateRoom::getName() const
        {
            return "CreateRoomCommand";
        }
    }
}
