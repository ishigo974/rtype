//
// Created by naliwe on 23/11/15.
//

#include <iostream>
#include "Object.hpp"

Object::Object()
{ }

Object::Object(unsigned int _id, std::string const& _name)
        : _id(_id), _name(_name)
{ }

Object::Object(Object const& other)
{
    _id   = other.getId();
    _name = other.getName();
}

Object::Object(Object&& other)
        : Object(other)
{
    swap(other);
}

Object& Object::operator=(Object other)
{
    swap(other);

    return (*this);
}

std::string Object::toString()
{
    std::stringstream ss;

    ss << "Object {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n}" << std::endl;


    return (ss.str());
}

unsigned int Object::getId() const
{
    return _id;
}

void Object::setId(unsigned int _id)
{
    Object::_id = _id;
}

std::string const& Object::getName() const
{
    return _name;
}

void Object::setName(std::string const& _name)
{
    Object::_name = _name;
}

void Object::swap(Object& other)
{
    using std::swap;

    swap(_name, other._name);
    swap(_id, other._id);
}

namespace std {
    template<>
    void swap<Object>(Object &a, Object &b)
    {
        a.swap(b);
    }
}

bool Object::operator==(Object const& other)
{
    return (
            _name == other.getName() &&
            _id == other.getId()
    );
}

bool Object::operator!=(Object const& other)
{
    return (!Object::operator==(other));
}

bool Object::findMask(RTypes::my_uint16_t)
{
    return false;
}
