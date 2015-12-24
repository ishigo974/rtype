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
            virtual void    update(double lastElapsed);

        public:
            void            setIsFiring(bool isFiring);
            void            setShotType(Shot::Type shotType);
            void            addLives(unsigned int nb = 1);
            void            removeLives(unsigned int nb = 1);
            void            addScore(unsigned int nb = 1);
            void            removeScore(unsigned int nb = 1);
            void            setElapsedTime(double elapsedTime);

        public:
            bool            isFiring() const;
            Shot::Type      getShotType() const;
            unsigned int    getLives() const;
            unsigned int    getScore() const;
            double          getElapsedTime() const;

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask     mask;
            static const unsigned int           defaultLives;
            static const unsigned int           usecFireDelay;
            static const double                 dftElapsedTime;

        protected:
            bool            _isFiring;
            Shot::Type      _shotType;
            unsigned int    _lives;
            unsigned int    _score;
            Time::HRChrono  _chrono;
            double          _elapsedTime;
        };
    }
}

#endif /* !SHIPCOMPONENT_HPP_ */
