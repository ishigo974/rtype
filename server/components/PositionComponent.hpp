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
            Position(unsigned int x = 0, unsigned int y = 0);
            virtual ~Position();

        public:
            Position(Position const& other);
            Position&               operator=(Position const& other);

        public:
            unsigned int            getX() const;
            unsigned int            getY() const;

        public:
            void                    setX(unsigned int x);
            void                    setY(unsigned int y);

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask     mask;

        protected:
            unsigned int    _x;
            unsigned int    _y;
        };
    }
}

#endif /* !POSITIONCOMPONENT_HPP_ */
