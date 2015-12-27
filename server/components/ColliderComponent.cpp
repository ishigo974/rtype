#include "ColliderComponent.hpp"
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
        const ECS::ComponentMask    Collider::mask  = MASK_COLLIDER;

        /*
        ** Constructor/Destructor
        */
        Collider::Collider(unsigned int x, unsigned int y,
                           unsigned int width, unsigned int height) :
            _bounds(x, y, width, height)
        {
        }

        Collider::~Collider()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Collider::Collider(Collider const& other) : _bounds(other._bounds)
        {
        }

        Collider&             Collider::operator=(Collider const& other)
        {
            if (this != &other)
                _bounds = other._bounds;
            return *this;
        }

        /*
        ** Public member functions
        */
        void                Collider::update()
        {
            Component::Position*    pos =
                ECS::EntityManager::getInstance().getByCmpnt(this)
                    .getComponent<Component::Position>();

            if (pos == nullptr)
                throw std::runtime_error("Collider: Missing position "
                                         "component");
            _bounds.x = pos->getX();
            _bounds.y = pos->getY();
        }

        bool                Collider::intersects(Collider const& other) const
        {
            return _bounds.intersects(other._bounds);
        }

        gu::Rect<int>       Collider::getBounds() const
        {
            return _bounds;
        }


        std::string         Collider::getName() const
        {
            return "Collider";
        }

        ECS::ComponentMask  Collider::getMask() const
        {
            return mask;
        }

        ECS::IComponent*    Collider::clone() const
        {
            return new Collider(*this);
        }

        void                Collider::clear()
        {
            _bounds = gu::Rect<int>();
        }

        std::string         Collider::toString() const
        {
            return "Collider {"
                  "\n}\n";
        }
    }
}
