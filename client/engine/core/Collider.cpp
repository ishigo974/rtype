//
// Created by naliwe on 01/12/15.
//

#include "Collider.hpp"

Collider::Collider() : Component()
{

}

Collider::Collider(unsigned int _id, std::string const& _name) : Component(_id, _name)
{

}

Collider::Collider(Collider const& other) : Component(other)
{

}

Collider::Collider(Collider&& other) : Collider(other)
{

}

//Collider& Collider::operator=(Collider other)
//{
//    return Collider::operator=(other); // WTF sale fiotte de merde. Et ca veut passer Koala. // vhb
//}

Collider::~Collider()
{

}

bool Collider::operator==(Collider const& other)
{
    return Component::operator==(other);
}

bool Collider::operator!=(Collider const& other)
{
    return Component::operator!=(other);
}

void Collider::swap(Collider& other)
{
    Component::swap(other);
}

RTypes::my_uint16_t Collider::getMask() const
{
    return Component::getMask();
}

std::string Collider::toString()
{
    return Component::toString();
}
