#ifndef MOBTYPEFACTORY_HPP_
# define MOBTYPEFACTORY_HPP_

# include "BaseFactory.hpp"
# include "IMobType.hpp"

namespace RType
{
    namespace Mob
    {
        class TypeFactory : public Utils::BaseFactory<IMobType>
        {
        public:
            TypeFactory();
            virtual ~TypeFactory();

        private:
            TypeFactory(TypeFactory const& other) = delete;
            TypeFactory&     operator=(TypeFactory const& other) = delete;
        };
    }
}

#endif /* !MOBTYPEFACTORY_HPP_ */
