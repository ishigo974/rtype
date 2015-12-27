#include <iostream>
#include "ComponentsMasks.hpp"
#include "UsernameCommand.hpp"
#include "ValueError.hpp"
#include "Server.hpp"
#include "Request.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructors/Destructor
        */
        Username::Username() : Command::Request()
        {
        }

        Username::~Username()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Username::Username(Username const& other) :
            Command::Request(other), _usernameToSet(other._usernameToSet),
            _oldUsername(other._oldUsername),
            _player(other._player), _network(other._network)
        {
        }

        Username&       Username::operator=(Username const& other)
        {
            if (this != &other)
            {
                Command::Request::operator=(other);
                _usernameToSet = other._usernameToSet;
                _oldUsername = other._oldUsername;
                _player = other._player;
                _network = other._network;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void    Username::execute()
        {
            Component::Room*    room;

            if (_player == nullptr || _network == nullptr)
                throw std::runtime_error("Entity does not have a \
player/network component");
            _player->setUsername(_usernameToSet);
            _network->send(Server::responseOK);
            if ((room = _player->getRoom()) != nullptr)
            {
                RType::Request     request(RType::Request::SE_CLIUSRNM);

                request.push<uint8_t>("player_id", room->getPlayerId(*_entity));
                request.push<std::string>("username", _usernameToSet);
                room->broadcastTCP(request.toBuffer(), _entity);
            }
        }

        void    Username::undo()
        {
        }

        void    Username::initFromRequest(RType::Request const& request,
                                          ECS::ASystem* sys)
        {
            _usernameToSet = request.get<std::string>("username");
            _system = sys;
        }

        Command::Request*   Username::clone() const
        {
            return new Username(*this);
        }

        std::string Username::getName() const
        {
            return "UsernameCommand";
        }

        void                Username::setEntity(ECS::Entity& entity)
        {
            Request::setEntity(entity);
            updateData();
        }

        /*
        ** Protected member functions
        */
        void        Username::updateData()
        {
            if ((_player = _entity->getComponent<Component::Player>())
                    == nullptr)
                return ;
            _oldUsername = _player->getUsername();
            if ((_network = _entity
                    ->getComponent<Component::NetworkTCP>()) == nullptr)
                return ;
        }
    }
}
