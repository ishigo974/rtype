#include <chrono>
#include "Collider.hpp"
#include "GameObject.hpp"
#include "EntityManager.hpp"

Collider::Collider() : Component()
{ }

Collider::Collider(unsigned int _id, std::string const& _name, int width, int height)
        : Component(_id, _name), _bounds(0, 0, width, height), _enabled(true)
{ }

Collider::Collider(Collider const& other) : Component(other)
{
    _bounds = other._bounds;
}

Collider::Collider(Collider&& other) : Collider(other)
{
    swap(other);
}

Collider& Collider::operator=(Collider other)
{
    swap(other);

    return (*this);
}

Collider::~Collider()
{ }

bool Collider::operator==(Collider const& other)
{
    return (Component::operator==(other) &&
            _bounds == other._bounds);
}

bool Collider::operator!=(Collider const& other)
{
    return Component::operator!=(other);
}

void Collider::swap(Collider& other)
{
    using std::swap;

    swap(_bounds, other._bounds);
}

RTypes::my_uint16_t Collider::getMask() const
{
    return (Mask);
}

std::string Collider::toString() const
{
    std::string ss;

    ss = "Collider {";
    ss += "\n\tid: ";
    ss += _id;
    ss += "\n\tname: ";
    ss += _name;
    ss += "\n\tmask: ";
    ss += Mask;
    ss += "\n}\n";

    return (ss);
}

void Collider::fixedUpdate(double)
{
    _bounds.x = static_cast<int>(static_cast<GameObject *>(parent())->transform().getPosition().X());
    _bounds.y = static_cast<int>(static_cast<GameObject *>(parent())->transform().getPosition().Y());
}

namespace std
{
    template<>
    inline void swap<Collider>(Collider& a, Collider& b)
    {
        a.swap(b);
    }
}

bool Collider::intersects(Collider *o) const
{
    return (_bounds.intersects(o->_bounds));
}

bool        Collider::isEnabled() const
{
    return _enabled;
}

void        Collider::setEnabled(bool e)
{
    _enabled = e;
}

void Collider::setRect(gu::Rect<int> const& r)
{
    _bounds = r;
}
