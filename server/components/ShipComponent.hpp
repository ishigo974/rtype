#ifndef SHIPCOMPONENT_HPP_
# define SHIPCOMPONENT_HPP_

# include <string>
# include "ComponentMask.hpp"
# include "IComponent.hpp"
# include "ShotComponent.hpp"

namespace RType
{
    namespace Component
    {
        class Ship : public ECS::IComponent
        {
        public:
            Ship();
            virtual ~Ship();

        public:
            Ship(Ship const& other);
            Ship&           operator=(Ship const& other);

        public:
            void            setIsFiring(bool isFiring);
            void            setShotType(Shot::Type shotType);
            void            addLives(unsigned int nb = 1);
            void            removeLives(unsigned int nb = 1);
            void            addScore(unsigned int nb = 1);
            void            removeScore(unsigned int nb = 1);

        public:
            bool            isFiring() const;
            Shot::Type      getShotType() const;
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
            bool            _isFiring;
            Shot::Type      _shotType;
            unsigned int    _lives;
            unsigned int    _score;
        };
    }
}

#endif /* !SHIPCOMPONENT_HPP_ */
