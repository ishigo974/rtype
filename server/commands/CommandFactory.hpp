#ifndef COMMANDFACTORY_HPP_
# define COMMANDFACTORY_HPP_

# include "BaseFactory.hpp"
# include "RequestCommand.hpp"

namespace RType
{
    namespace Command
    {
        class Factory : public Utils::BaseFactory<Command::Request>
        {
        public:
            Factory();
            virtual ~Factory();

        private:
            Factory(Factory const& other) = delete;
            Factory&     operator=(Factory const& other) = delete;
        };
    }
}

#endif /* !COMMANDFACTORY_HPP_ */
