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
                throw std::runtime_error("Can't initialize command: \
expected LobbySystem"); // TODO
            _room = lobby->getRoom(request.get<uint32_t>("room_id"));
        }

        void        JoinRoom::execute()
        {
            Component::Player*      player =
                _entity->getComponent<Component::Player>(Component::MASK_PLAYER);
            Component::NetworkTCP*  network =
                _entity->getComponent<Component::NetworkTCP>(
                    Component::MASK_NETWORKTCP);

            if (player == nullptr || network == nullptr)
                throw std::runtime_error("Entity does not have a \
player/network component");
            if (_room == nullptr || player->getRoom() != nullptr
                || !_room->addPlayer(*_entity))
                network->send(Server::responseKO);
            else
            {
                Buffer          buffer;
                unsigned int    id;

                player->setRoom(_room);
                id = _room->getPlayerId(*_entity);
                _room->broadcast(buildJoinRoomAlert(id, player->getUsername()),
                                _entity);
                network->send(buildRoomInfos(_room->getPlayersMap(), id));
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
        Buffer      JoinRoom::buildJoinRoomAlert(uint8_t id,
                                                 std::string const& username)
        {
            Buffer  buffer;

            buffer.append<uint16_t>(RType::Request::SE_JOINROOM);
            buffer.append<uint32_t>(sizeof(uint8_t) + sizeof(uint32_t) +
                                    username.size());
            buffer.append<uint8_t>(id);
            buffer.append<uint32_t>(username.size());
            buffer.append<std::string>(username);
            return buffer;
        }

        Buffer      JoinRoom::buildRoomInfos(Component::Room::PlayersMap const&
                                             players, unsigned int id)
        {
            Buffer  res;
            Buffer  buffer;

            buffer.append<uint8_t>(id);
            for (auto& player: players)
            {
                if (player.first == id)
                    continue ;
                Component::Player*  c = player.second.first
                    ->getComponent<Component::Player>(Component::MASK_PLAYER);

                buffer.append<uint8_t>(player.first);
                buffer.append<uint32_t>(c->getUsername().size());
                buffer.append<std::string>(c->getUsername());
                buffer.append<uint8_t>(player.second.second);
            }
            res.append<uint16_t>(RType::Request::SE_ROOMINFO);
            res.append<uint32_t>(buffer.size());
            res.append(buffer);
            return res;
        }
    }
}
