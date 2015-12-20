#ifndef SHOTFIRINGSYSTEM_HPP_
# define SHOTFIRINGSYSTEM_HPP_

# include <unordered_map>
# include <string>
# include "ASystem.hpp"
# include "Entity.hpp"
# include "ComponentMask.hpp"

namespace RType
{
    namespace System
    {
        class ShotFiring : public ECS::ASystem
        {
        public:
            ShotFiring();
            virtual ~ShotFiring();

        private:
            ShotFiring(ShotFiring const& other) = delete;
            ShotFiring&     operator=(ShotFiring const& other) = delete;

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

#endif /* !SHOTFIRINGSYSTEM_HPP_ */
