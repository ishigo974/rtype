#include <sstream>
#include "Player.hpp"
#include "ComponentsMasks.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Constructor/Destructor
        */
        Player::Player()
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

        std::string         Player::getName() const
        {
            return "Player";
        }

        ECS::ComponentMask  Player::getMask() const
        {
            return MASK_PLAYER;
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
