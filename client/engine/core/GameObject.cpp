//
// Created by naliwe on 23/11/15.
//

#include <iostream>
#include "GameObject.hpp"

GameObject::GameObject()
{ }

GameObject::GameObject(unsigned int _id, std::string const& _name, int _layer)
        : Object(_id, _name), _layer(_layer)
{ }

GameObject::GameObject(GameObject const& other) : Object(other)
{
    _layer = other.getLayer();
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

std::string GameObject::toString()
{
    std::stringstream ss;

    ss << "GameObject {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tlayer: " << _layer
    << "\n}" << std::endl;

    return (ss.str());
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
}

namespace std {
    template<>
    void swap<GameObject>(GameObject &a, GameObject &b)
    {
        a.swap(b);
    }
}

unsigned int GameObject::getMask()
{
    return 0;
}

Transform const* GameObject::getTransform()
{
    return (dynamic_cast<Transform *>(_components[0].get()));
}

void GameObject::addComponent(std::unique_ptr<Component> newComp)
{
    _components.push_back(std::move(newComp));
}
