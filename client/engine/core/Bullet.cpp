#include <iostream>
#include "Bullet.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Player.hpp"

Bullet::Bullet()
{
}

Bullet::Bullet(unsigned int _id, std::string const& _name, int hp, int damage)
  : Behaviour(_id, _name), _hp(hp), _damage(damage)
{
  _direction = Bullet::Direction::DEFAULT;
}

Bullet::Bullet(Bullet const& other) : Behaviour(other)
{
    _hp = other._hp;
    _damage = other._damage;
    _direction = other._direction;
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

    ss << "Player {"
       << "\n\thp: " << _hp
       << "\n\tdamage: " << _damage
       << "\n\tdirection: " << _direction
       << "\n\t" << transform.toString()
       << "\n}" << std::endl;

    return (ss.str());
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

void		Bullet::setDirection(Bullet::Direction d)
{
  _direction = d;
}

void		Bullet::init()
{
  GameObject	*obj = static_cast<GameObject*>(EntityManager::getParentOf(this));
  Transform	&_transform = static_cast<GameObject *>(parent())->transform();

  _transform.getPosition().setX(obj->transform().getPosition().X());
  _transform.getPosition().setY(obj->transform().getPosition().Y());
  _direction = Bullet::RIGHT;
}

void		Bullet::move(Transform & transform)
{
  float		speed = 10.0f;

  if (!_enabled)
    return ;
  transform.getPosition().setX((transform.getPosition().X() + _direction * speed));
}

void		Bullet::update(double)
{
  Transform	&transform = static_cast<GameObject *>(parent())->transform();

  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move(transform);
}
