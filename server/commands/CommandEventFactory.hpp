#ifndef COMMANDEVENTFACTORY_HPP_
# define COMMANDEVENTFACTORY_HPP_

# include "BaseFactory.hpp"
# include "EventCommand.hpp"

namespace RType
{
    namespace Command
    {
        class EventFactory : public Utils::BaseFactory<Command::Event>
        {
        public:
            EventFactory();
            virtual ~EventFactory();

        private:
            EventFactory(EventFactory const& other) = delete;
            EventFactory&     operator=(EventFactory const& other) = delete;
        };
    }
}

#endif /* !COMMANDEVENTFACTORY_HPP_ */
