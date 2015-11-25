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
    swap(*this, other);
}

Object& Object::operator=(Object other)
{
    swap(*this, other);

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

void Object::swap(Object& first, Object& second)
{
    std::swap(first._name, second._name);
    std::swap(first._id, second._id);
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

unsigned int Object::getMask()
{
    return 0;
}
