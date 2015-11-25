//
// Created by naliwe on 23/11/15.
//

#include "Component.hpp"

Component::Component()
{ }

Component::Component(uint _id, std::string const& _name, u_int16_t _mask)
        : Object(_id, _name), _mask(_mask)
{ }

Component::Component(Component const& other) : Object(other)
{
    _mask = other.getMask();
}

Component::Component(Component&& other) : Component(other)
{
    swap(*this, other);
}

Component& Component::operator=(Component other)
{
    swap(*this, other);

    return (*this);
}

Component::~Component()
{ }

bool Component::operator==(Component const& other)
{
    return (Object::operator==(other) &&
            _mask == other.getMask());
}

bool Component::operator!=(Component const& other)
{
    return (!Component::operator==(other));
}

void Component::swap(Component& first, Component& second)
{
    std::swap(first._mask, second._mask);
}

u_int16_t Component::getMask() const
{
    return _mask;
}

void Component::setMask(u_int16_t _mask)
{
    Component::_mask = _mask;
}

std::string Component::toString()
{
    std::stringstream ss;

    ss << "Component {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tmask: " << _mask
    << "\n}" << std::endl;

    return (ss.str());
}
