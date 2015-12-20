#ifndef EVENTCOMMAND_HPP_
# define EVENTCOMMAND_HPP_

# include <string>
# include "ICommand.hpp"
# include "Entity.hpp"
# include "InGameEvent.hpp"
# include "ASystem.hpp"

namespace RType
{
    namespace Command
    {
        class Event : public ICommand
        {
        public:
            Event();
            Event(ECS::Entity* entity);
            virtual ~Event();

        public:
            Event(Event const& other);
            Event&              operator=(Event const& other);

        public:
            virtual void        setEntity(ECS::Entity& entity);
            virtual std::string toString() const;

        public:
            virtual void        initFromEvent(InGameEvent const& request) = 0;
            virtual Event*      clone() const = 0;
            virtual std::string getName() const = 0;

        protected:
            ECS::Entity*            _entity;
        };
    }
}

#endif /* !EVENTCOMMAND_HPP_ */
