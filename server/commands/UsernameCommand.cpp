#include "ComponentsMasks.hpp"
#include "UsernameCommand.hpp"
#include "ValueError.hpp"
#include "Server.hpp"

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
            // validation username TODO
            if (_player != nullptr)
                _player->setUsername(_usernameToSet);
            if (_network != nullptr)
                _network->send(Server::responseOK);
            // broadcast to room TODO
        }

        void    Username::undo()
        {
            if (_player != nullptr)
                _player->setUsername(_oldUsername);
            if (_network != nullptr)
                _network->send(Server::responseOK);
            // broadcast to room TODO
        }

//        void    Username::setEntity(ECS::Entity* entity)
//        {
//            _entity = entity;
//            updateData();
//        }

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

        /*
        ** Protected member functions
        */
        void        Username::updateData()
        {
            if ((_player = _entity
                    ->getComponent<Component::Player>(Component::MASK_PLAYER))
                        == nullptr)
                return ;
            _oldUsername = _player->getUsername();
            if ((_network = _entity
                    ->getComponent<Component::NetworkTCP>(
                        Component::MASK_NETWORKTCP)) == nullptr)
                return ;
        }
    }
}
