#ifndef CREATEROOMCOMMAND_HPP_
# define CREATEROOMCOMMAND_HPP_

# include <string>
# include "Request.hpp"
# include "RequestCommand.hpp"
# include "ASystem.hpp"
# include "LobbySystem.hpp"

namespace RType
{
    namespace Command
    {
        class CreateRoom : Command::Request
        {
        public:
            CreateRoom();
            virtual ~CreateRoom();

        public:
            CreateRoom(CreateRoom const& other);
            CreateRoom&         operator=(CreateRoom const& other);

        public:
            virtual void        initFromRequest(RType::Request const& request,
                                                ECS::ASystem* system);
            virtual void        execute();
            virtual void        undo();
            virtual Request*    clone() const;

        public:
            virtual std::string getName() const;

        protected:
            std::string         _roomName;
            System::Lobby*      _lobby;
        };
    }
}

#endif /* !CREATEROOMCOMMAND_HPP_ */
