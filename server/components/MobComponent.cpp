#include "MobComponent.hpp"
#include "PositionComponent.hpp"
#include "ComponentsMasks.hpp"
#include "Utils.hpp"
#include "EntityManager.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Mob::mask   = Component::MASK_MOB;

        /*
        ** Constructor/Destructor
        */
        Mob::Mob() :
            _id(0), _name(""), _lives(0),
            _scoreValue(0), _spriteFilePath(""), _state(1)
        {
        }

        Mob::Mob(MobType::IMobType const* type) :
            _id(0), _name(""), _lives(0),
            _scoreValue(0), _spriteFilePath(""), _state(1)
        {
            init(type);
        }

        Mob::~Mob()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Mob::Mob(Mob const& other) :
            _id(other._id), _name(other._name), _lives(other._lives),
            _scoreValue(other._scoreValue), _spriteFilePath(other._spriteFilePath),
            _movePattern(other._movePattern), _state(other._state)
        {
        }

        Mob&           Mob::operator=(Mob const& other)
        {
            if (this != &other)
            {
                _id = other._id;
                _name = other._name;
                _lives = other._lives;
                _scoreValue = other._scoreValue;
                _spriteFilePath = other._spriteFilePath;
                _movePattern = other._movePattern;
                _state = other._state;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void            Mob::init(MobType::IMobType const* type)
        {
            _id = type->getId();
            _name = type->getName();
            _lives = type->getNbLives();
            _scoreValue = type->getScoreValue();
            _spriteFilePath = type->getSpriteFilePath();
            _movePattern = type->getMovePattern();
        }

        void            Mob::update()
        {
            Component::Position*    pos = ECS::EntityManager::getInstance()
                .getByCmpnt(this).getComponent<Component::Position>();
            cu::Position            newpos =
                _movePattern(cu::Position(pos->getX(), pos->getY()), 1.0, _state);

            pos->setX(newpos.X());
            pos->setY(newpos.Y());
            // TODO with elapsed time
        }

        void            Mob::addLives(unsigned int nb)
        {
            _lives += nb;
        }

        void            Mob::removeLives(unsigned int nb)
        {
            if (nb > _lives)
                _lives = 0;
            else
                _lives -= nb;
        }

        unsigned int            Mob::getId() const
        {
            return _id;
        }

        std::string const&      Mob::getMobName() const
        {
            return _name;
        }

        unsigned int            Mob::getLives() const
        {
            return _lives;
        }

        unsigned int            Mob::getScoreValue() const
        {
            return _scoreValue;
        }

        std::string const&      Mob::getSpriteFilePath() const
        {
            return _spriteFilePath;
        }

        MobType::MovePattern const&      Mob::getMovePattern() const
        {
            return _movePattern;
        }

        std::string         Mob::getName() const
        {
            return "MobComponent";
        }

        ECS::ComponentMask  Mob::getMask() const
        {
            return mask;
        }

        ECS::IComponent*    Mob::clone() const
        {
            return new Mob(*this);
        }

        void                Mob::clear()
        {
            _id = 0;
            _name = "";
            _lives = 0;
            _scoreValue = 0;
            _spriteFilePath = "";
            _movePattern = MobType::MovePattern();
            _state = 1;
        }

        std::string         Mob::toString() const
        {
            return "Component::Mob {"
                   "\n\t_id: " + std::to_string(_id) +
                   "\n\t_name: " + _name +
                   "\n\t_lives: " + std::to_string(_lives) +
                   "\n\t_scoreValue: " + std::to_string(_scoreValue) +
                   "\n\t_spriteFilePath: " + _spriteFilePath +
                   "\n\t_state: " + std::to_string(_state) +
                   "\n}\n";
        }
    }
}
