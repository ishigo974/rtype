#ifndef LOBBYSYSTEM_HPP_
# define LOBBYSYSTEM_HPP_

# include <string>
# include "Entity.hpp"
# include "ASystem.hpp"
# include "ComponentMask.hpp"

namespace RType
{
    namespace System
    {
        class Lobby : public ECS::ASystem
        {
        public:
            Lobby();
            virtual ~Lobby();

        private:
            Lobby(Lobby const& other) = delete;
            Lobby&      operator=(Lobby const& other) = delete;

        public:
            virtual void                processEntity(ECS::Entity& e);
            virtual ECS::ComponentMask  getMask() const;
            virtual std::string         getName() const;
            virtual std::string         toString() const;
        };
    }
}

#endif /* !LOBBYSYSTEM_HPP_ */
