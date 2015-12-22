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

std::string Component::toString() const
{
    std::string ss;

    ss += "Component {";
    ss += "\n\tid: ";
    ss += _id;
    ss += "\n\tname: ";
    ss += _name;
    ss += "\n\tmask: ";
    ss += Mask;
    ss += "\n}\n";

    return (ss);
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

Object *Component::parent() const
{
    return (EntityManager::getParentOf(this));
}

bool Component::handleMessage(Collider *)
{
    return (false);
}