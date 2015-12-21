#ifndef MOBTYPEFACTORY_HPP_
# define MOBTYPEFACTORY_HPP_

# include "BaseFactory.hpp"
# include "IMobType.hpp"

namespace RType
{
    namespace MobType
    {
        class Factory : public Utils::BaseFactory<IMobType>
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

#endif /* !MOBTYPEFACTORY_HPP_ */
