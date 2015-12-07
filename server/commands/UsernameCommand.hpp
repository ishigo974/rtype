#ifndef USERNAMECOMMAND_HPP_
# define USERNAMECOMMAND_HPP_

# include <string>
# include "ACommand.hpp"
# include "Request.hpp"
# include "Player.hpp"
# include "Entity.hpp"

namespace RType
{
    namespace Command
    {
        class Username : public ACommand
        {
        public:
            Username();
            virtual ~Username();

        public:
            Username(Username const& other);
            Username&           operator=(Username const& other);

        public:
            void                setUsernameToSet(std::string const& username);

        public:
            virtual void        execute();
            virtual void        undo();
            virtual void        setEntity(ECS::Entity* entity);
            virtual void        initFromRequest(Request const& request);
            virtual ACommand*   clone() const;

        public:
            virtual std::string getName() const;

        protected:
            void                updateData();

        public:
            std::string         _usernameToSet;
            std::string         _oldUsername;
            Component::Player*  _player;
        };
    }
}

#endif /* !USERNAMECOMMAND_HPP_ */
