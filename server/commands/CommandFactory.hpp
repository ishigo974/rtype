#ifndef COMMANDFACTORY_HPP_
# define COMMANDFACTORY_HPP_

# include "BaseFactory.hpp"
# include "ACommand.hpp"

namespace RType
{
    namespace Command
    {
        class Factory : public Utils::BaseFactory<ACommand>
        {
        protected:
            Factory();
            virtual ~Factory();

        protected:
            Factory(Factory const& other) = delete;
            Factory&     operator=(Factory const& other) = delete;
        };
    }
}

#endif /* !COMMANDFACTORY_HPP_ */
