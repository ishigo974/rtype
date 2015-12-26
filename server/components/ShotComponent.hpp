#ifndef SHOTCOMPONENT_HPP_
# define SHOTCOMPONENT_HPP_

# include <string>
# include "ComponentMask.hpp"
# include "IBehaviour.hpp"
# include "GameComponent.hpp"
# include "Entity.hpp"

namespace RType
{
    namespace Component
    {
        class Shot : public ECS::IBehaviour
        {
        public:
            enum Type
            {
                NORMAL = 0,
            };

        public:
            Shot(Shot::Type type = NORMAL, ECS::Entity* owner = nullptr,
                 Component::Game* game = nullptr);
            virtual ~Shot();

        public:
            Shot(Shot const& other);
            Shot&                       operator=(Shot const& other);

        public:
            virtual void                update();

        public:
            Type                        getType() const;
            void                        setType(Type type);
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
            Type                _type;
            ECS::Entity*        _owner;
            Component::Game*    _game;
        };
    }
}

#endif /* !SHOTCOMPONENT_HPP_ */
