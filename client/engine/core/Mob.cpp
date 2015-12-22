#include <iostream>
#include "Mob.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Collider.hpp"
#include "Player.hpp"

Mob::Mob()
{
}

Mob::Mob(unsigned int _id, std::string const& _name, int hp, int damage, int type) :
    Behaviour(_id, _name), _hp(hp), _damage(damage), _type(type), _transform(0)
{
    _enabled = true;
    _direction = 1;
}

Mob::Mob(Mob const& other) : Behaviour(other)
{
    _enabled = other._enabled;
    _hp = other._hp;
    _damage = other._damage;
    _direction = other._direction;
    _type = other._type;
    _transform = other._transform;
}

Mob::Mob(Mob&& other) : Mob(other)
{
    swap(other);
}

Mob& Mob::operator=(Mob other)
{
    swap(other);

    return (*this);
}

Mob::~Mob()
{
}

bool Mob::operator==(Mob const& other)
{
    return (Behaviour::operator==(other));
}

bool Mob::operator!=(Mob const& other)
{
    return (!Mob::operator==(other));
}

void Mob::swap(Mob& other)
{
    using std::swap;

    swap(_enabled, other._enabled);
    swap(_hp, other._hp);
    swap(_damage, other._damage);
    swap(_direction, other._direction);
    swap(_type, other._type);
    swap(_transform, other._transform);
}

namespace std
{
    template<>
    void swap<Mob>(Mob& a, Mob& b)
    {
        a.swap(b);
    }
}

std::string Mob::toString() const
{
    std::stringstream ss;

    ss << "Player {"
    << "\n\thp: " << _hp
    << "\n\tdamage: " << _damage
    << "\n\ttype: " << _type
    << "\n\tGraphic height: " << _graphicHeight;
    if (_transform)
    ss << "\n\t" << _transform->toString();
    ss << "\n}" << std::endl;

    return (ss.str());
}

int	Mob::getHp() const
{
    return _hp;
}

int	Mob::getDamage() const
{
    return _damage;
}

void		Mob::move()
{
    float		speed = 0.5f;

    _graphicHeight = static_cast<GameObject *>(parent())->renderer().getRect().h;
    switch (_type)
    {
        case 0:
            if (_transform->getPosition().Y() <= 0)
                _direction = 1;
        else if (_transform->getPosition().Y() >= Renderer::height - _graphicHeight)
            _direction = -1;
            _transform->getPosition().setY((_transform->getPosition().Y() + _direction * speed));
            break;
        case 1:
            if (_transform->getPosition().Y() >= Renderer::height - _graphicHeight)
                _type = 2;
            _direction = -1;
            _transform->getPosition().setY((_transform->getPosition().Y() + _direction * -1 * speed));
            _transform->getPosition().setX((_transform->getPosition().X() + _direction * speed * 3 / 4));
            break;
        case 2:
            if (_transform->getPosition().Y() <= 0)
                _type = 1;
            _direction = -1;
            _transform->getPosition().setY((_transform->getPosition().Y() + _direction * speed));
            _transform->getPosition().setX((_transform->getPosition().X() + _direction * speed * 3 / 4));
            break;
        case 3:
            _direction = -1;
            _transform->getPosition().setX((_transform->getPosition().X() + _direction * speed));
            break;
        default:
            _type = 3;
            break;
    }
}

void		Mob::update(double)
{
    GameObject	*p = static_cast<GameObject *>(parent());

    if (_hp <= 0)
    {
        std::cout << "Mob Mort" << std::endl;
        _enabled = false;
        p->setVisible(false);
        p->getComponent<Collider>()->setEnabled(false);
    }
    if (!_transform)
        _transform = p->getComponent<Transform>();
    if (_transform->getPosition().X() > Renderer::width + 100
    || _transform->getPosition().X() < -100
    || _transform->getPosition().Y() > Renderer::height + 100
    || _transform->getPosition().Y() < -100)
        _enabled = false;
    this->move();
}

bool Mob::handleMessage(Collider *o)
{
    GameObject	*otherParent = static_cast<GameObject *>(o->parent());
    if (otherParent->getComponent<Player>() != nullptr)
        _hp -= otherParent->getComponent<Player>()->getDamage();
    else if (otherParent->getComponent<Behaviour>() != nullptr)
        _hp -= otherParent->getComponent<Behaviour>()->getDamage();
    return (true);
}
