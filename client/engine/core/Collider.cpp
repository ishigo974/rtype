//
// Created by naliwe on 01/12/15.
//

#include "Collider.hpp"

Collider::Collider() : Component()
{ }

Collider::Collider(unsigned int _id, std::string const& _name) : Component(_id, _name)
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

std::string Collider::toString()
{
    //TODO : _bounds.toSting()
    std::stringstream ss;

    ss << "Collider {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tmask: " << Mask
    << "\n}" << std::endl;

    return (ss.str());
}

namespace std
{
    template<>
    void swap<Collider>(Collider& a, Collider& b)
    {
        a.swap(b);
    }
}
