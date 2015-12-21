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
  _damage = 5;
  _available = true;
  _transform = 0;
}

Bullet::Bullet(unsigned int _id, std::string const& _name)
  : Behaviour(_id, _name)
{
  _direction = Bullet::Direction::DEFAULT;
  _hp = 1;
  _damage = 5;
  _available = true;
  _transform = 0;
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
  if (!_transform)
    _transform = static_cast<GameObject *>(parent())->getComponent<Transform>();
  _transform->getPosition().setX(x);
}

void		Bullet::setY(float y)
{
  if (!_transform)
    _transform = static_cast<GameObject *>(parent())->getComponent<Transform>();
  _transform->getPosition().setY(y);
}

void	Bullet::setAvailable(bool a)
{
  _available = a;
}

bool	Bullet::getAvailable() const
{
  return _available;
}

void		Bullet::setDirection(Bullet::Direction d)
{
  _direction = d;
}

void		Bullet::move(double elapsedtime)
{
  float		speed = 0.75f;

  _transform->getPosition().setX((_transform->getPosition().X() + _direction * speed * elapsedtime));
}

void		Bullet::update(double elapsedtime)
{
  if (!_transform)
    _transform = static_cast<GameObject *>(parent())->getComponent<Transform>();
  if (_transform->getPosition().X() > Renderer::width)
    _available = true;
  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move(elapsedtime);
}
