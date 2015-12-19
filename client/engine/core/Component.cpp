#include "Component.hpp"
#include "EntityManager.hpp"

Component::Component()
{ }

Component::Component(unsigned int _id, std::string const& _name)
        : Object(_id, _name)
{ }

Component::Component(Component const& other) : Object(other)
{ }

Component::Component(Component&& other) : Component(other)
{
    swap(other);
}

Component& Component::operator=(Component other)
{
    swap(other);

    return (*this);
}

Component::~Component()
{ }

bool Component::operator==(Component const& other)
{
    return (Object::operator==(other) &&
            Mask == other.getMask());
}

bool Component::operator!=(Component const& other)
{
    return (!Component::operator==(other));
}

RTypes::my_uint16_t Component::getMask() const
{
    return Mask;
}

std::string Component::toString()
{
    std::stringstream ss;

    ss << "Component {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tmask: " << Mask
    << "\n}" << std::endl;

    return (ss.str());
}

void Component::swap(Component& other)
{
    using std::swap;

    swap(_id, other._id);
    swap(_name, other._name);
}

namespace std
{
    template<>
    inline void swap<Component>(Component& a, Component& b)
    {
        a.swap(b);
    }
}

Object *Component::parent()
{
    return (EntityManager::getParentOf(this));
}
