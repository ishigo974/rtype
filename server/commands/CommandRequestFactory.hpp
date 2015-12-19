#ifndef COMMANDFACTORY_HPP_
# define COMMANDFACTORY_HPP_

# include "BaseFactory.hpp"
# include "RequestCommand.hpp"

namespace RType
{
    namespace Command
    {
        class RequestFactory : public Utils::BaseFactory<Command::Request>
        {
        public:
            RequestFactory();
            virtual ~RequestFactory();

        private:
            RequestFactory(RequestFactory const& other) = delete;
            RequestFactory&     operator=(RequestFactory const& other) = delete;
        };
    }
}

#endif /* !COMMANDFACTORY_HPP_ */