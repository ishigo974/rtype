#ifndef USERNAMECOMMAND_HPP_
# define USERNAMECOMMAND_HPP_

# include <string>
# include "Request.hpp"
# include "RequestCommand.hpp"
# include "Player.hpp"
# include "NetworkTCP.hpp"
# include "Entity.hpp"
# include "ASystem.hpp"

namespace RType
{
    namespace Command
    {
        class Username : public Command::Request
        {
        public:
            Username();
            virtual ~Username();

        public:
            Username(Username const& other);
            Username&           operator=(Username const& other);

        public:
            virtual void        initFromRequest(RType::Request const& request,
                                                ECS::ASystem* system);
            virtual void        execute();
            virtual void        undo();
            virtual void        setEntity(ECS::Entity* entity);
            virtual Request*    clone() const;

        public:
            virtual std::string getName() const;

        protected:
            void                updateData();

        public:
            std::string             _usernameToSet;
            std::string             _oldUsername;
            Component::Player*      _player;
            Component::NetworkTCP*  _network;
        };
    }
}

#endif /* !USERNAMECOMMAND_HPP_ */
