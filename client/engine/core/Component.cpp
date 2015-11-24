#include <stdint.h>
#include "Component.hpp"

Component::Component()
{ }

Component::Component(unsigned int _id, std::string const& _name) : Object(_id, _name)
{ }

Component::Component(Component const& other) : Object(other)
{ }

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
    return (Object::operator==(other));
}

bool Component::operator!=(Component const& other)
{
    return (!Component::operator==(other));
}

void Component::swap(Component& first, Component& second)
{

}
