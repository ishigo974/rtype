#include "ShipComponent.hpp"
#include "ShotComponent.hpp"
#include "PlayerComponent.hpp"
#include "RoomComponent.hpp"
#include "ComponentsMasks.hpp"
#include "PositionComponent.hpp"
#include "EntityManager.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Ship::mask              = Component::MASK_SHIP;
        const unsigned int          Ship::defaultLives      = 1;

        /*
        ** Constructor/Destructor
        */
        Ship::Ship() :
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
            _lives(other._lives), _score(other._score)
        {
        }

        Ship&                       Ship::operator=(Ship const& other)
        {
            if (this != &other)
            {
                _lives = other._lives;
                _score = other._score;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void                Ship::update()
        {
        }

        void                Ship::fire(unsigned int shot_type)
        {
            ECS::EntityManager&     em      = ECS::EntityManager::getInstance();
            ECS::Entity&            entity  = em.getByCmpnt(this);
            Component::Position*    pos     =
                entity.getComponent<Component::Position>();
            Component::Room*        room    =
                entity.getComponent<Component::Player>()->getRoom();

            if (_chrono.getElapsedTime() > RType::Shot::usecFireDelay)
            {
                ECS::Entity&            shot    =
                    em.create(Component::MASK_POSITION);
                Component::Position*    shotPos =
                    shot.getComponent<Component::Position>();
                Component::Game*        game    =
                    em.getByCmpnt(room).getComponent<Component::Game>();

                shot.addComponent(
                    std::make_unique<Component::Shot>(
                        static_cast<RType::Shot::Type>(shot_type),
                            &entity, game));
                shotPos->setX(pos->getX() + RType::Ship::width);
                shotPos->setY(pos->getY());
                _chrono.reset();
                // std::cout << "Fire" << std::endl;
            }
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
            _lives = defaultLives;
            _score = 0;
        }

        std::string         Ship::toString() const
        {
            return "Component::Ship {"
                   "\n\t_lives: " + std::to_string(_lives) +
                   "\n\t_score: " + std::to_string(_score) +
                   "\n}\n";
        }
    }
}
