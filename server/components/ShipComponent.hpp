#ifndef SHIPCOMPONENT_HPP_
# define SHIPCOMPONENT_HPP_

# include <string>
# include "ComponentMask.hpp"
# include "IBehaviour.hpp"
# include "ShotComponent.hpp"
# include "HRChrono.hpp"

namespace RType
{
    namespace Component
    {
        class Ship : public ECS::IBehaviour
        {
        public:
            Ship();
            virtual ~Ship();

        public:
            Ship(Ship const& other);
            Ship&           operator=(Ship const& other);

        public:
            virtual void    update();
            void            fire(unsigned int shot_type);

        public:
            void            addLives(unsigned int nb = 1);
            void            removeLives(unsigned int nb = 1);
            void            addScore(unsigned int nb = 1);
            void            removeScore(unsigned int nb = 1);

        public:
            unsigned int    getLives() const;
            unsigned int    getScore() const;

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask     mask;
            static const unsigned int           defaultLives;

        protected:
            unsigned int    _lives;
            unsigned int    _score;
            Time::HRChrono  _chrono;
        };
    }
}

#endif /* !SHIPCOMPONENT_HPP_ */
