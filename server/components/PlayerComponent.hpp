#ifndef PLAYERCOMPONENT_HPP_
# define PLAYERCOMPONENT_HPP_

# include <string>
# include "IComponent.hpp"
# include "Entity.hpp"
# include "RoomComponent.hpp"

namespace RType
{
    namespace Component
    {
        class Player : public ECS::IComponent
        {
        public:
            Player();
            virtual ~Player();

        public:
            Player(Player const& other);
            Player&                 operator=(Player const& other);

        public:
            std::string const&      getUsername() const;
            void                    setUsername(std::string const& username);
            Component::Room*        getRoom() const;
            void                    setRoom(Component::Room* room);

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual IComponent*         clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const std::string    defaultUsername;

        protected:
            std::string         _username;
            Component::Room*    _room;
        };
    }
}

#endif /* !PLAYERCOMPONENT_HPP_ */
