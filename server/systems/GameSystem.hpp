#ifndef GAMESYSTEM_HPP_
# define GAMESYSTEM_HPP_

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
        class Game : public ECS::ASystem
        {
        public:
            typedef std::unique_ptr<MobType::IMobType>  UniqueMobType;
            typedef std::unordered_map<unsigned int,
                                       UniqueMobType>   MobTypeMap;

        public:
            Game(MobType::Collection const& mobTypes = MobType::Collection());
            virtual ~Game();

        private:
            Game(Game const& other) = delete;
            Game&     operator=(Game const& other) = delete;

        public:
            MobTypeMap const&           getMobsTypes() const;

        public:
            virtual void                update();
            virtual void                processEntity(ECS::Entity& e);
            virtual ECS::ComponentMask  getMask() const;
            virtual std::string         getName() const;
            virtual bool                shouldAutoUpdate() const;
            virtual bool                shouldAutoProcess() const;
            virtual std::string         toString() const;

        protected:
            MobTypeMap                  _mobTypes;
        };
    }
}

#endif /* !GAMESYSTEM_HPP_ */
