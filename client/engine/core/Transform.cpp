//
// Created by fourdr_b on 27/11/15.
//

#include "Transform.hpp"

Transform::Transform() : Component()
{ }

Transform::Transform(unsigned int _id, std::string const& _name, RTypes::my_uint16_t _mask,
                     cu::Position const& pos, cu::Scale scale, cu::Rotation rot)
        : Component(_id, _name, _mask),
          _position(pos), _scale(scale), _rotation(rot)
{ }

Transform::Transform(Transform const& other) : Component(other)
{
    _position = other.getPosition();
    _scale    = other.getScale();
    _rotation = other.getRotation();
}

Transform::Transform(Transform&& other) : Transform(other)
{
    std::swap(*this, other);
}

Transform& Transform::operator=(Transform other)
{
    std::swap(*this, other);

    return (*this);
}

Transform::~Transform()
{ }

bool Transform::operator==(Transform const& other)
{
    return (_position == other.getPosition() &&
            _scale == other.getScale() &&
            _rotation == other.getRotation());
}

bool Transform::operator!=(Transform const& other)
{
    return (!Transform::operator==(other));
}

std::string Transform::toString()
{
    std::stringstream ss;

    ss << "Transform {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tPosition: " << _position.toString()
    << "\n\tScale: " << _scale.toString()
    << "\n\tRotation: " << _rotation.toString()
    << "\n}" << std::endl;

    return (ss.str());
}

void Transform::swap(Transform& second)
{
    using std::swap;

    swap(_position, second._position);
    swap(_scale, second._scale);
    swap(_rotation, second._rotation);
}

cu::Position const& Transform::getPosition() const
{
    return _position;
}

void Transform::setPosition(cu::Position const& _position)
{
    Transform::_position = _position;
}

cu::Scale const& Transform::getScale() const
{
    return _scale;
}

void Transform::setScale(cu::Scale const& _scale)
{
    Transform::_scale = _scale;
}

cu::Rotation const& Transform::getRotation() const
{
    return _rotation;
}

void Transform::setRotation(cu::Rotation const& _rotation)
{
    Transform::_rotation = _rotation;
}