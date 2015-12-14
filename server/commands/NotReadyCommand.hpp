#ifndef NOTREADYCOMMAND_HPP_
# define NOTREADYCOMMAND_HPP_

# include <string>
# include "Request.hpp"
# include "RequestCommand.hpp"
# include "ASystem.hpp"

namespace RType
{
    namespace Command
    {
        class NotReady : public Command::Request
        {
        public:
            NotReady();
            virtual ~NotReady();

        public:
            NotReady(NotReady const& other);
            NotReady&           operator=(NotReady const& other);

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

#endif /* !NOTREADYCOMMAND_HPP_ */
