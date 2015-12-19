#include "Behaviour.hpp"

Behaviour::Behaviour()
{ }

Behaviour::Behaviour(unsigned int _id, std::string const& _name)
  : Component(_id, _name)
{ }

Behaviour::Behaviour(Behaviour const& other) : Component(other)
{
    _enabled = other.isEnabled();
}

Behaviour::Behaviour(Behaviour&& other) : Behaviour(other)
{
    swap(other);
}

Behaviour& Behaviour::operator=(Behaviour other)
{
    swap(other);

    return (*this);
}

Behaviour::~Behaviour()
{ }

bool Behaviour::operator==(Behaviour const& other)
{
    return (Component::operator==(other));
}

bool Behaviour::operator!=(Behaviour const& other)
{
    return (!Behaviour::operator==(other));
}

void Behaviour::swap(Behaviour& other)
{
    using std::swap;

    swap(_enabled, other._enabled);
}

namespace std
{
    template<>
    inline void swap<Behaviour>(Behaviour& a, Behaviour& b)
    {
        a.swap(b);
    }
}

bool Behaviour::isEnabled() const
{
    return (_enabled);
}

void Behaviour::setEnabled(bool _enabled)
{
    Behaviour::_enabled = _enabled;
}

void Behaviour::update(double)
{
    if (!_enabled)
        return;
}

void Behaviour::update()
{
    if (!_enabled)
        return;
}

RTypes::my_uint16_t Behaviour::getMask() const
{
    return Mask;
}
