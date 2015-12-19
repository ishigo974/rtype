#include <sstream>
#include "PlayerComponent.hpp"
#include "ComponentsMasks.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const std::string           Player::defaultUsername = "Player";
        const ECS::ComponentMask    Player::mask            = MASK_PLAYER;

        /*
        ** Constructor/Destructor
        */
        Player::Player() : _username(Player::defaultUsername), _room(nullptr)
        {
        }

        Player::~Player()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Player::Player(Player const& other) : _username(other._username)
        {
        }

        Player&             Player::operator=(Player const& other)
        {
            if (this != &other)
                _username = other._username;
            return *this;
        }

        /*
        ** Public member functions
        */
        std::string const&  Player::getUsername() const
        {
            return _username;
        }

        void                Player::setUsername(std::string const& username)
        {
            _username = username;
        }

        Component::Room*    Player::getRoom() const
        {
            return _room;
        }

        void                Player::setRoom(Component::Room* room)
        {
            _room = room;
        }

        std::string         Player::getName() const
        {
            return "Player";
        }

        ECS::ComponentMask  Player::getMask() const
        {
            return mask;
        }

        ECS::IComponent*    Player::clone() const
        {
            return new Player(*this);
        }

        void                Player::clear()
        {
            _username.clear();
        }

        std::string         Player::toString() const
        {
            std::ostringstream  ss;

            ss << "Player {"
                << "\n\t_username: " << _username
                << "\n}\n";
            return ss.str();
        }
    }
}
