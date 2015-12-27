//
// Created by naliwe on 23/11/15.
//

#include <iostream>
#include "GameObject.hpp"

GameObject::GameObject()
{ }

GameObject::GameObject(unsigned int _id, std::string const& _name, int _layer)
  : Object(_id, _name), _layer(_layer), _isVisible(true)
{ }

GameObject::GameObject(GameObject const& other) : Object(other)
{
    _layer = other.getLayer();
    _isVisible = other._isVisible;
}

GameObject::GameObject(GameObject&& other) : GameObject(other)
{
    swap(other);
}

GameObject& GameObject::operator=(GameObject other)
{
    swap(other);

    return (*this);
}

GameObject::~GameObject()
{
    _components.clear();
}

bool GameObject::operator==(GameObject const& other)
{
    return (Object::operator==(other) &&
            _layer == other.getLayer());
}

bool GameObject::operator!=(GameObject const& other)
{
    return (!GameObject::operator==(other));
}

std::string GameObject::toString() const
{
    std::string ss;
    
    ss = "GameObject {";
    ss += "\n\tid: ";
    ss += _id;
    ss += "\n\tname: ";
    ss +=_name;
    ss += "\n\tlayer: ";
    ss += _layer;
    ss += "\n\tTransform: " + getComponent<Transform>()->toString();
    ss += "\n}\n";

    return (ss);
}

int GameObject::getLayer() const
{
    return _layer;
}

void GameObject::setLayer(unsigned int _layer)
{
    GameObject::_layer = _layer;
}

void GameObject::swap(GameObject& other)
{
    using std::swap;

    swap(_layer, other._layer);
    swap(_isVisible, other._isVisible);
}

namespace std
{
    template<>
    inline void swap<GameObject>(GameObject& a, GameObject& b)
    {
        a.swap(b);
    }
}

bool GameObject::findMask(RTypes::my_uint16_t mask)
{
    for (auto comp : _components)
    {
        if ((comp->getMask() & mask) == mask)
            return true;
    }
    return false;
}

void GameObject::addComponent(Component *const newComp)
{
    _components.push_back(newComp);
}

Transform& GameObject::transform() const
{
    Transform *tmp = getComponent<Transform>();

    if (tmp == nullptr)
        throw std::runtime_error("Transform not found");
    return (*tmp);
}

SpriteRenderer& GameObject::renderer() const
{
    SpriteRenderer *tmp = getComponent<SpriteRenderer>();

    if (tmp == nullptr)
        throw std::runtime_error("Renderer not found");
    return (*tmp);
}

bool		GameObject::isVisible() const
{
    return _isVisible;
}

void		GameObject::setVisible(bool v)
{
    _isVisible = v;
}
