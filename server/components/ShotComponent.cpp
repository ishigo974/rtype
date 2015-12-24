#include "ShotComponent.hpp"
#include "PositionComponent.hpp"
#include "ComponentsMasks.hpp"
#include "EntityManager.hpp"
#include "GameConfig.hpp"
#include "GameComponent.hpp"
#include "PlayerComponent.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Shot::mask      = Component::MASK_SHOT;
        const float                 Shot::speed     = 0.75f;

        /*
        ** Constructor/Destructor
        */
        Shot::Shot(Shot::Type type, ECS::Entity* owner) :
            _type(type), _owner(owner)
        {
        }

        Shot::~Shot()
        {
        }

        /*
        ** Copy constructor/Assign operator
        */
        Shot::Shot(Shot const& other) : _type(other._type), _owner(other._owner)
        {
        }

        Shot&               Shot::operator=(Shot const& other)
        {
            if (this != &other)
            {
                _type = other._type;
                _owner = other._owner;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void                Shot::update(double lastElapsed)
        {
            ECS::EntityManager&     em = ECS::EntityManager::getInstance();
            Component::Position*    pos =
                em.getByCmpnt(this).getComponent<Component::Position>();

            if (pos == nullptr)
                return ;
            switch (_type)
            {
                case NORMAL:
                    pos->setX(pos->getX() + (speed * lastElapsed));
                    break ;
                default:
                    break ;
            }
            std::cout << this << " Shot moved to " << pos->getX() << " " << pos->getY()  << " " << lastElapsed << std::endl; // debug
            if (pos->getX() <= 0 || pos->getX() >= Map::width
                || pos->getY() <= 0 || pos->getY() >= Map::height)
            {
                ECS::EntityManager& em = ECS::EntityManager::getInstance();

                em.safeDestroy(em.getByCmpnt(this));
                std::cout << "safedestroy bullet" << std::endl;
            }
        }

        Shot::Type          Shot::getType() const
        {
            return _type;
        }

        void                Shot::setType(Type type)
        {
            _type = type;
        }

        ECS::Entity*        Shot::getOwner() const
        {
            return _owner;
        }

        void                Shot::setOwner(ECS::Entity* owner)
        {
            _owner = owner;
        }

        std::string         Shot::getName() const
        {
            return "ShotComponent";
        }

        ECS::ComponentMask  Shot::getMask() const
        {
            return mask;
        }

        ECS::IComponent*    Shot::clone() const
        {
            return new Shot(*this);
        }

        void                Shot::clear()
        {
            _type = NORMAL;
        }

        std::string         Shot::toString() const
        {
            return "ShotComponent {\n\t_type: " +
                   std::to_string(static_cast<int>(_type)) + "}\n";
        }
    }
}
