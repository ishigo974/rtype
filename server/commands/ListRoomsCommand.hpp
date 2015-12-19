#ifndef LISTROOMSCOMMAND_HPP_
# define LISTROOMSCOMMAND_HPP_

# include <string>
# include "Request.hpp"
# include "RequestCommand.hpp"
# include "ASystem.hpp"
#include "LobbySystem.hpp"

namespace RType
{
    namespace Command
    {
        class ListRooms : public Command::Request
        {
        public:
            ListRooms();
            virtual ~ListRooms();

        public:
            ListRooms(ListRooms const& other);
            ListRooms&         operator=(ListRooms const& other);

        public:
            virtual void        initFromRequest(RType::Request const& request,
                                                ECS::ASystem* system);
            virtual void        execute();
            virtual void        undo();
            virtual Request*    clone() const;

        public:
            virtual std::string getName() const;

        protected:
            System::Lobby::RoomsMap const*  _rooms;
        };
    }
}

#endif /* !LISTROOMSCOMMAND_HPP_ */
