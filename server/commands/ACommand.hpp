#ifndef ACOMMAND_HPP_
# define ACOMMAND_HPP_

# include <string>
# include "ICommand.hpp"
# include "Entity.hpp"
# include "Request.hpp"

namespace RType
{
    namespace Command
    {
        class ACommand : public ICommand
        {
        public:
            ACommand();
            ACommand(ECS::Entity* entity);
            virtual ~ACommand();

        public:
            ACommand(ACommand const& other);
            ACommand&               operator=(ACommand const& other);

        public:
            virtual void            setEntity(ECS::Entity* entity);
            virtual std::string     toString() const;

        public:
            virtual void            initFromRequest(Request const& request) = 0;
            virtual ACommand*       clone() const = 0;
            virtual std::string     getName() const = 0;

        protected:
            ECS::Entity*            _entity;
        };
    }
}

#endif /* !ACOMMAND_HPP_ */
