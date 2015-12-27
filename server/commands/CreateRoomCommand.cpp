#include <iostream>
#include <random>
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
                throw std::runtime_error("Can't initialize command: "
"expected LobbySystem");
            _roomName = request.get<std::string>("room_name");
        }

        void        CreateRoom::execute()
        {
            ECS::Entity&                e =
                ECS::EntityManager::getInstance().create(Component::MASK_ROOM);
            Component::Room*            room = e.getComponent<Component::Room>();
            Component::Player*          player =
                _entity->getComponent<Component::Player>();
            Component::NetworkTCP*      network =
                _entity->getComponent<Component::NetworkTCP>();
            Map::Collection const&      maps = _lobby->getMaps();
            std::random_device          seed;
            std::default_random_engine  random_engine(seed());

            std::uniform_int_distribution<int> uid(0, maps.size());

            if (room == nullptr || player == nullptr || network == nullptr)
                throw std::runtime_error("Entity does not have a "
                                         "room/player/network component");
            if (maps.empty())
                throw std::runtime_error("No maps loaded");
            room->addPlayer(*_entity);
            room->setName(_roomName);
            room->setMap(&maps.at(uid(random_engine)));
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
