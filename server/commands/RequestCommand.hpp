#ifndef REQUESTCOMMAND_HPP_
# define REQUESTCOMMAND_HPP_

# include <string>
# include "ICommand.hpp"
# include "Entity.hpp"
# include "Request.hpp"
# include "ASystem.hpp"

namespace RType
{
    namespace Command
    {
        class Request : public ICommand
        {
        public:
            Request();
            Request(ECS::Entity* entity);
            virtual ~Request();

        public:
            Request(Request const& other);
            Request&         operator=(Request const& other);

        public:
            virtual void        setEntity(ECS::Entity& entity);
            virtual std::string toString() const;

        public:
            virtual void        initFromRequest(RType::Request const& request,
                                                ECS::ASystem* system) = 0;
            virtual Request*    clone() const = 0;
            virtual std::string getName() const = 0;

        protected:
            ECS::Entity*            _entity;
            ECS::ASystem*           _system;
        };
    }
}

#endif /* !REQUESTCOMMAND_HPP_ */
