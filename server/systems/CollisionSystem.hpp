#ifndef COLLISIONSYSTEM_HPP_
# define COLLISIONSYSTEM_HPP_

# include <unordered_map>
# include <string>
# include <memory>
# include "ASystem.hpp"
# include "Entity.hpp"
# include "ComponentMask.hpp"
# include "IMobType.hpp"

namespace RType
{
    namespace System
    {
        class Collision : public ECS::ASystem
        {
        public:
            Collision();
            virtual ~Collision();

        private:
            Collision(Collision const& other) = delete;
            Collision&          operator=(Collision const& other) = delete;

        public:
            virtual void                update();
            virtual void                processEntity(ECS::Entity& e);
            virtual ECS::ComponentMask  getMask() const;
            virtual std::string         getName() const;
            virtual bool                shouldAutoUpdate() const;
            virtual bool                shouldAutoProcess() const;
            virtual std::string         toString() const;

        protected:
        };
    }
}

#endif /* !COLLISIONSYSTEM_HPP_ */
