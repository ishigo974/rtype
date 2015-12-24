#ifndef POSITIONCOMPONENT_HPP_
# define POSITIONCOMPONENT_HPP_

# include <string>
# include "ComponentMask.hpp"
# include "IComponent.hpp"

namespace RType
{
    namespace Component
    {
        class Position : public ECS::IComponent
        {
        public:
            Position(float x = 0, float y = 0);
            virtual ~Position();

        public:
            Position(Position const& other);
            Position&               operator=(Position const& other);

        public:
            float       getX() const;
            float       getY() const;

        public:
            void        setX(float x);
            void        setY(float y);

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask     mask;

        protected:
            float    _x;
            float    _y;
        };
    }
}

#endif /* !POSITIONCOMPONENT_HPP_ */
