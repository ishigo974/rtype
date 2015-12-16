#ifndef READYCOMMAND_HPP_
# define READYCOMMAND_HPP_

# include <string>
# include "Request.hpp"
# include "RequestCommand.hpp"
# include "ASystem.hpp"
# include "RoomComponent.hpp"

namespace RType
{
    namespace Command
    {
        class Ready : public Command::Request
        {
        public:
            Ready();
            virtual ~Ready();

        public:
            Ready(Ready const& other);
            Ready&              operator=(Ready const& other);

        public:
            virtual void        initFromRequest(RType::Request const& request,
                                                ECS::ASystem* system);
            virtual void        execute();
            virtual void        undo();
            virtual Request*    clone() const;

        public:
            virtual std::string getName() const;

        protected:
            void                startGame(Component::Room* room) const;
        };
    }
}

#endif /* !READYCOMMAND_HPP_ */
