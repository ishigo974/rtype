#include <iostream>
#include "Bullet.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

Bullet::Bullet()
{
    _direction = Bullet::Direction::DEFAULT;
    _hp = 1;
    _damage = 1;
    _available = true;
    _transform = 0;
    _parent = nullptr;
}

Bullet::Bullet(unsigned int _id, std::string const& _name)
    : Behaviour(_id, _name)
{
    _direction = Bullet::Direction::DEFAULT;
    _hp = 1;
    _damage = 5;
    _available = true;
    _transform = 0;
    _parent = nullptr;
}

Bullet::Bullet(Bullet const& other) : Behaviour(other)
{
    _hp = other._hp;
    _damage = other._damage;
    _direction = other._direction;
    _enabled = other._enabled;
    _available = other._available;
    _transform = other._transform;
}

Bullet::Bullet(Bullet&& other) : Bullet(other)
{
    swap(other);
}

Bullet& Bullet::operator=(Bullet other)
{
    swap(other);

    return (*this);
}

Bullet::~Bullet()
{
}

bool Bullet::operator==(Bullet const& other)
{
    return (Behaviour::operator==(other));
}

bool Bullet::operator!=(Bullet const& other)
{
    return (!Bullet::operator==(other));
}

void Bullet::swap(Bullet& other)
{
    using std::swap;

    swap(_enabled, other._enabled);
    swap(_hp, other._hp);
    swap(_damage, other._damage);
    swap(_direction, other._direction);
    swap(_available, other._available);
    swap(_transform, other._transform);
}

namespace std
{
    template<>
    inline void swap<Bullet>(Bullet& a, Bullet& b)
    {
        a.swap(b);
    }
}

void	Bullet::setHp(int hp)
{
    _hp = hp;
}

void	Bullet::setDamage(int damage)
{
    _damage = damage;
}

int	Bullet::getHp() const
{
    return _hp;
}

int	Bullet::getDamage() const
{
    return _damage;
}

std::string Bullet::toString() const
{
    std::stringstream ss;

    ss << "Bullet {"
    << "\n\thp: " << _hp
    << "\n\tdamage: " << _damage
    << "\n\tdirection: " << _direction
    << "\n\tavailable: " << _available
    << "\n\tenabled: " << _enabled;
    if (_transform)
        ss << "\n\t" << _transform->toString();
    ss << "\n}" << std::endl;

    return (ss.str());
}

RTypes::my_uint16_t     Bullet::getMask() const
{
    return Mask;
}

float		Bullet::getX() const
{
    return _transform->getPosition().X();
}

float		Bullet::getY() const
{
    return _transform->getPosition().Y();
}

void		Bullet::setX(float x)
{
    _transform->getPosition().setX(x);
}

void		Bullet::setY(float y)
{
    _transform->getPosition().setY(y);
}

void	Bullet::setAvailable(bool a)
{
    _available = a;
}

void    Bullet::init()
{
    if (!_parent)
        _parent = static_cast<GameObject *>(parent());
    if (!_transform)
        _transform = static_cast<GameObject *>(parent())->getComponent<Transform>();
}

bool	Bullet::getAvailable() const
{
    return _available;
}

void		Bullet::setDirection(Bullet::Direction d)
{
    _direction = d;
}

void		Bullet::move(double elapsedtime) const
{
    _transform->getPosition().setX((_transform->getPosition().X() + _direction *
                                    RType::Speed::bullet *
                                    static_cast<float>(elapsedtime)));
}

void		Bullet::update(double elapsedtime)
{
    if (_hp <= 0 || _transform->getPosition().X() > Renderer::width)
        _available = true;
    this->move(elapsedtime);
}

bool Bullet::handleMessage(Collider *)
{
    _hp = 0;
    return (true);
}
