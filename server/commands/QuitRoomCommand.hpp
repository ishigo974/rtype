#ifndef QUITROOMCOMMAND_HPP_
# define QUITROOMCOMMAND_HPP_

# include <string>
# include "Request.hpp"
# include "RequestCommand.hpp"
# include "ASystem.hpp"

namespace RType
{
    namespace Command
    {
        class QuitRoom : public Command::Request
        {
        public:
            QuitRoom();
            virtual ~QuitRoom();

        public:
            QuitRoom(QuitRoom const& other);
            QuitRoom&           operator=(QuitRoom const& other);

        public:
            virtual void        initFromRequest(RType::Request const& request,
                                                ECS::ASystem* system);
            virtual void        execute();
            virtual void        undo();
            virtual Request*    clone() const;

        public:
            virtual std::string getName() const;
        };
    }
}

#endif /* !QUITROOMCOMMAND_HPP_ */
