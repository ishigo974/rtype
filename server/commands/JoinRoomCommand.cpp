#include <iostream>
#include "JoinRoomCommand.hpp"
#include "EntityManager.hpp"
#include "ComponentsMasks.hpp"
#include "RoomComponent.hpp"
#include "PlayerComponent.hpp"
#include "LobbySystem.hpp"
#include "NetworkTCP.hpp"
#include "Server.hpp"
#include "Request.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructor/Destructor
        */
        JoinRoom::JoinRoom() : _room(nullptr)
        {
        }

        JoinRoom::~JoinRoom()
        {
        }


        /*
        ** Copy constructor and assign operator
        */
        JoinRoom::JoinRoom(JoinRoom const& other) :
            Command::Request(other), _room(other._room)
        {
        }

        JoinRoom&     JoinRoom::operator=(JoinRoom const& other)
        {
            if (this != &other)
            {
                Command::Request::operator=(other);
                _room = other._room;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void        JoinRoom::initFromRequest(RType::Request const& request,
                                                ECS::ASystem* sys)
        {
            System::Lobby*  lobby;

            if ((lobby = dynamic_cast<System::Lobby*>(sys)) == nullptr)
                throw std::runtime_error("Can't initialize command: "
                                         "expected LobbySystem");
            _room = lobby->getRoom(request.get<uint32_t>("room_id"));
        }

        void        JoinRoom::execute()
        {
            Component::Player*      player =
                _entity->getComponent<Component::Player>();
            Component::NetworkTCP*  network =
                _entity->getComponent<Component::NetworkTCP>();

            if (player == nullptr || network == nullptr)
                throw std::runtime_error("Entity does not have a "
                                         "player/network component");
            if (_room == nullptr || player->getRoom() != nullptr
                || !_room->addPlayer(*_entity))
                network->send(Server::responseKO);
            else
            {
                RType::Request         request(RType::Request::SE_JOINROOM);

                player->setRoom(_room);
                request.push<uint8_t>("player_id",
                                      _room->getPlayerId(*_entity));
                request.push<std::string>("username", player->getUsername());
                _room->broadcastTCP(request.toBuffer(), _entity);
                network->send(buildRoomInfos(_room->getPlayersMap(),
                                             _room->getPlayerId(*_entity)));
            }
        }

        void        JoinRoom::undo()
        {
        }

        Request*    JoinRoom::clone() const
        {
            return new JoinRoom(*this);
        }

        std::string JoinRoom::getName() const
        {
            return "JoinRoomCommand";
        }

        /*
        ** Protected member functions
        */
        Buffer      JoinRoom::buildRoomInfos(Component::Room::PlayersMap const&
                                             players, unsigned int id)
        {
            RType::Request  request(RType::Request::SE_ROOMINFO);
            Buffer          buffer;

            request.push<uint8_t>("player_id", id);
            for (auto& player: players)
            {
                if (player.first == id)
                    continue ;
                Component::Player*  c = player.second.first
                    ->getComponent<Component::Player>();

                buffer.append<uint8_t>(player.first);
                buffer.append<uint32_t>(c->getUsername().size());
                buffer.append<std::string>(c->getUsername());
                buffer.append<uint8_t>(player.second.second);
            }
            request.push<Buffer>("players", buffer);
            return request.toBuffer();
        }
    }
}
