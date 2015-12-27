#ifndef COLLIDERCOMPONENT_HPP_
# define COLLIDERCOMPONENT_HPP_

# include <string>
# include "IBehaviour.hpp"
# include "Entity.hpp"
# include "Rect.hpp"

namespace RType
{
    namespace Component
    {
        class Collider : public ECS::IBehaviour
        {
        public:
            Collider(unsigned int width = 0, unsigned int height = 0);
            virtual ~Collider();

        public:
            Collider(Collider const& other);
            Collider&                   operator=(Collider const& other);

        public:
            virtual void                update();
            bool                        intersects(Collider const& other) const;

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual IComponent*         clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask mask;

        protected:
            gu::Rect<int>               _bounds;
        };
    }
}

#endif /* !COLLIDERCOMPONENT_HPP_ */
