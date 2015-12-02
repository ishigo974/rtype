#include "ICommand.hpp"
#include "Entity.hpp"

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
            ACommand&       operator=(ACommand const& other);

        protected:
            ECS::Entity*    _entity;
        };
    }
}
