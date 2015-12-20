#include "ShotComponent.hpp"
#include "PositionComponent.hpp"
#include "ComponentsMasks.hpp"
#include "EntityManager.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    Shot::mask  =   Component::MASK_SHOT;

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
        void                Shot::update()
        {
            Component::Position*    pos =
                ECS::EntityManager::getInstance().getByCmpnt(this)
                    .getComponent<Component::Position>();

            if (pos == nullptr)
                return ;
            switch (_type)
            {
                case NORMAL:
                    pos->setX(pos->getX() + 10); // TODO
                    break ;
                default:
                    break ;
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
