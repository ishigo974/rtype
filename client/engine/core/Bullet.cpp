#include <iostream>
#include "Bullet.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

Bullet::Bullet()
{
  _direction = Bullet::Direction::DEFAULT;
  // _transform = new Transform(0, cu::Position(0, 0));
  _hp = 1;
  _damage = 5;
  _available = true;
  // visible = false;
}

Bullet::Bullet(unsigned int _id, std::string const& _name)
  : Behaviour(_id, _name)
{
  _direction = Bullet::Direction::DEFAULT;
  // _transform = new Transform(0, cu::Position(0, 0));
  _available = true;
  _hp = 1;
  _damage = 5;
  // visible = false;
}

Bullet::Bullet(Bullet const& other) : Behaviour(other)
{
    _hp = other._hp;
    _damage = other._damage;
    _direction = other._direction;
    _available = other._available;
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
}

namespace std
{
    template<>
    inline void swap<Bullet>(Bullet& a, Bullet& b)
    {
        a.swap(b);
    }
}

RTypes::my_uint16_t     Bullet::getMask() const
{
  return Mask;
}

int	Bullet::getHp() const
{
  return _hp;
}

int	Bullet::getDamage() const
{
  return _damage;
}

std::string Bullet::toString()
{
    std::stringstream ss;
    Transform	&transform = static_cast<GameObject *>(parent())->transform();

    ss << "Bullet {"
       << "\n\thp: " << _hp
       << "\n\tdamage: " << _damage
       << "\n\tdirection: " << _direction
       << "\n\tavailable: " << _available
       << "\n\tenabled: " << _enabled
       << "\n\t" << transform.toString()
       << "\n}" << std::endl;

    return (ss.str());
}

float		Bullet::getX()
{
  Transform	&_transform = static_cast<GameObject *>(parent())->transform();

  return _transform.getPosition().X();
}

float		Bullet::getY()
{
  Transform	&_transform = static_cast<GameObject *>(parent())->transform();

  return _transform.getPosition().Y();
}

void		Bullet::setX(float x)
{
  Transform	&_transform = static_cast<GameObject *>(parent())->transform();

  _transform.getPosition().setX(x);
}

void		Bullet::setY(float y)
{
  Transform	&_transform = static_cast<GameObject *>(parent())->transform();

  _transform.getPosition().setY(y);
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

void		Bullet::move()
{
  float		speed = 10.0f;
  Transform	&_transform = static_cast<GameObject *>(parent())->transform();

  if (!_enabled)
    return ;
  _transform.getPosition().setX((_transform.getPosition().X() + _direction * speed));
}

void		Bullet::update(double)
{
  Transform	&_transform = static_cast<GameObject *>(parent())->transform();

  if (_transform.getPosition().X() > Renderer::width)
    _available = true;
  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move();
}
