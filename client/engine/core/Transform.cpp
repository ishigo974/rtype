//
// Created by fourdr_b on 27/11/15.
//

#include "Transform.hpp"

Transform::Transform() : Component()
{
}

Transform::Transform(unsigned int _id)
        : Component(_id, "Transform"), _position(0, 0), _scale(1, 1), _rotation(0)
{ }

Transform::Transform(unsigned int _id, cu::Position const& pos)
        : Component(_id, "Transform"), _position(pos)
{ }

Transform::Transform(unsigned int _id, std::string const& _name,
                     cu::Position const& pos,
                     cu::Scale const& scale,
                     cu::Rotation const& rot)
        : Component(_id, _name),
          _position(pos), _scale(scale), _rotation(rot)
{
}

Transform::Transform(Transform const& other) : Component(other)
{
    _position = other.getPosition();
    _scale    = other.getScale();
    _rotation = other.getRotation();
}

Transform::Transform(Transform&& other) : Transform(other)
{
    swap(other);
}

Transform& Transform::operator=(Transform other)
{
    swap(other);

    return (*this);
}

Transform::~Transform()
{
}

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

std::string Transform::toString() const
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

namespace std
{
    template<>
    inline void swap<Transform>(Transform& a, Transform& b)
    {
        a.swap(b);
    }
}

cu::Position& Transform::getPosition()
{
    return _position;
}

cu::Position const& Transform::getPosition() const
{
    return _position;
}

void Transform::setPosition(cu::Position const& _position)
{
    Transform::_position = _position;
}

cu::Scale& Transform::getScale()
{
    return _scale;
}

cu::Scale const& Transform::getScale() const
{
    return _scale;
}

void Transform::setScale(cu::Scale const& _scale)
{
    Transform::_scale = _scale;
}

cu::Rotation& Transform::getRotation()
{
    return _rotation;
}

cu::Rotation const& Transform::getRotation() const
{
    return _rotation;
}

void Transform::setRotation(cu::Rotation const& _rotation)
{
    Transform::_rotation = _rotation;
}
