#include "ShipComponent.hpp"
#include "ComponentsMasks.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Ship::mask          = Component::MASK_SHIP;
        const unsigned int          Ship::defaultLives  = 1;

        /*
        ** Constructor/Destructor
        */
        Ship::Ship() :
            _isFiring(false), _shotType(Shot::NORMAL),
            _lives(defaultLives), _score(0)
        {
        }

        Ship::~Ship()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Ship::Ship(Ship const& other) :
            _isFiring(other._isFiring), _shotType(other._shotType),
            _lives(other._lives), _score(other._score)
        {
        }

        Ship&                       Ship::operator=(Ship const& other)
        {
            if (this != &other)
            {
                _isFiring = other._isFiring;
                _shotType = other._shotType;
                _lives = other._lives;
                _score = other._score;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void                Ship::setIsFiring(bool isFiring)
        {
            _isFiring = isFiring;
        }

        void                Ship::setShotType(Shot::Type shotType)
        {
            _shotType = shotType;
        }

        void                Ship::addLives(unsigned int nb)
        {
            _lives += nb;
        }

        void                Ship::removeLives(unsigned int nb)
        {
            if (nb > _lives)
                _lives = 0;
            else
                _lives -= nb;
        }

        void                Ship::addScore(unsigned int nb)
        {
            _score += nb;
        }

        void                Ship::removeScore(unsigned int nb)
        {
            if (nb > _score)
                _score = 0;
            else
                _score -= nb;
        }

        bool                Ship::isFiring() const
        {
            return _isFiring;
        }

        Shot::Type          Ship::getShotType() const
        {
            return _shotType;
        }

        unsigned int        Ship::getLives() const
        {
            return _lives;
        }

        unsigned int        Ship::getScore() const
        {
            return _score;
        }

        std::string         Ship::getName() const
        {
            return "ShipComponent";
        }

        ECS::ComponentMask  Ship::getMask() const
        {
            return mask;
        }

        ECS::IComponent*    Ship::clone() const
        {
            return new Ship(*this);
        }

        void                Ship::clear()
        {
            _isFiring = false;
            _shotType = Shot::NORMAL;
            _lives = defaultLives;
            _score = 0;
        }

        std::string         Ship::toString() const
        {
            return "Component::Ship {"
                   "\n\t_isFiring: " + std::to_string(_isFiring) +
                   "\n\t_shotType: " + std::to_string(_shotType) +
                   "\n\t_lives: " + std::to_string(_lives) +
                   "\n\t_score: " + std::to_string(_score) +
                   "\n}\n";
        }
    }
}
