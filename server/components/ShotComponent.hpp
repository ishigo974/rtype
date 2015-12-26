#ifndef SHOTCOMPONENT_HPP_
# define SHOTCOMPONENT_HPP_

# include <string>
# include "ComponentMask.hpp"
# include "IBehaviour.hpp"
# include "GameComponent.hpp"
# include "Entity.hpp"
# include "GameConfig.hpp"

namespace RType
{
    namespace Component
    {
        class Shot : public ECS::IBehaviour
        {
        public:
            Shot(RType::Shot::Type type = RType::Shot::NORMAL,
                 ECS::Entity* owner = nullptr,
                 Component::Game* game = nullptr);
            virtual ~Shot();

        public:
            Shot(Shot const& other);
            Shot&                       operator=(Shot const& other);

        public:
            virtual void                update();

        public:
            RType::Shot::Type           getType() const;
            void                        setType(RType::Shot::Type type);
            ECS::Entity*                getOwner() const;
            void                        setOwner(ECS::Entity* owner);
            Component::Game*            getGame() const;
            void                        setGame(Component::Game* game);

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask     mask;

        protected:
            RType::Shot::Type   _type;
            ECS::Entity*        _owner;
            Component::Game*    _game;
        };
    }
}

#endif /* !SHOTCOMPONENT_HPP_ */
