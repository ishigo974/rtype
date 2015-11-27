#include "GameObject.hpp"

GameObject::GameObject()
{ }

GameObject::GameObject(unsigned int _id, std::string const& _name, unsigned int _layer)
        : Object(_id, _name), _layer(_layer)
{ }

GameObject::GameObject(GameObject const& other) : Object(other)
{
    _layer = other.getLayer();
}

GameObject::GameObject(GameObject&& other) : GameObject(other)
{
    swap(*this, other);
}

GameObject& GameObject::operator=(GameObject other)
{
    swap(*this, other);

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

std::string const& GameObject::toString()
{
    if (_toString.empty())
    {
        std::stringstream ss;

        ss << "GameObject {"
        << "\n\tid: " << _id
        << "\n\tname: " << _name
        << "\n\tlayer: " << _layer
        << "\n}" << std::endl;

        _toString = ss.str();
    }

    return (_toString);
}

unsigned int GameObject::getLayer() const
{
    return _layer;
}

void GameObject::setLayer(unsigned int _layer)
{
    GameObject::_layer = _layer;
}

void GameObject::swap(GameObject& first, GameObject& second) const
{
    std::swap(first._layer, second._layer);
}
