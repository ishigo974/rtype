#include "JoinRoomCommand.hpp"
#include "EntityManager.hpp"
#include "ComponentsMasks.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include "LobbySystem.hpp"
#include "NetworkTCP.hpp"
#include "Server.hpp"

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
            // validation name TODO
            if (_room == nullptr || player->getRoom() != nullptr
                || _room->size() >= Component::Room::nbMaxPlayers)
                network->send(Server::responseKO);
            else
            {
                _room->addPlayer(*_entity);
                player->setRoom(_room);
                network->send(Server::responseOK);
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
    }
}
