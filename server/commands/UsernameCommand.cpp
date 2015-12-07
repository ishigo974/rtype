#include "ComponentsMasks.hpp"
#include "UsernameCommand.hpp"
#include "ValueError.hpp"

namespace RType
{
    namespace Command
    {
        /*
        ** Constructors/Destructor
        */
        Username::Username() : ACommand()
        {
        }

        Username::~Username()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Username::Username(Username const& other) :
            ACommand(other), _usernameToSet(other._usernameToSet),
            _oldUsername(other._oldUsername), _player(other._player)
        {
        }

        Username&       Username::operator=(Username const& other)
        {
            if (this != &other)
            {
                ACommand::operator=(other);
                _usernameToSet = other._usernameToSet;
                _oldUsername = other._oldUsername;
                _player = other._player;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void    Username::execute()
        {
            if (_player != nullptr)
                _player->setUsername(_usernameToSet);
        }

        void    Username::undo()
        {
            if (_player != nullptr)
                _player->setUsername(_oldUsername);
        }

        void    Username::setEntity(ECS::Entity* entity)
        {
            _entity = entity;
            updateData();
        }

        void    Username::initFromRequest(Request const& request)
        {
            _usernameToSet = request.get<std::string>("username");
        }

        ACommand*   Username::clone() const
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
        }
    }
}
