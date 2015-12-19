#ifndef JOINROOMCOMMAND_HPP_
# define JOINROOMCOMMAND_HPP_

# include <string>
# include "Request.hpp"
# include "RequestCommand.hpp"
# include "ASystem.hpp"
# include "RoomComponent.hpp"

namespace RType
{
    namespace Command
    {
        class JoinRoom : public Command::Request
        {
        public:
            JoinRoom();
            virtual ~JoinRoom();

        public:
            JoinRoom(JoinRoom const& other);
            JoinRoom&           operator=(JoinRoom const& other);

        public:
            virtual void        initFromRequest(RType::Request const& request,
                                                ECS::ASystem* system);
            virtual void        execute();
            virtual void        undo();
            virtual Request*    clone() const;

        public:
            virtual std::string getName() const;

        protected:
            Buffer          buildJoinRoomAlert(uint8_t id,
                                                std::string const& username);
            Buffer          buildRoomInfos(Component::Room::PlayersMap const&
                                            players, unsigned int id);

        protected:
            Component::Room*    _room;
        };
    }
}

#endif /* !JOINROOMCOMMAND_HPP_ */
