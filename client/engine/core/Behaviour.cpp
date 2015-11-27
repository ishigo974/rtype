//
// Created by fourdr_b on 26/11/15.
//

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
    swap(*this, other);
}

Behaviour& Behaviour::operator=(Behaviour other)
{
    swap(*this, other);

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

void Behaviour::swap(Behaviour& first, Behaviour& second)
{
    std::swap(first._enabled, second._enabled);
}

bool Behaviour::isEnabled() const
{
    return (_enabled);
}

void Behaviour::setEnabled(bool _enabled)
{
    Behaviour::_enabled = _enabled;
}

void Behaviour::update()
{
    if (!_enabled)
        return ;
}
