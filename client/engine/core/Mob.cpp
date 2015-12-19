#include <iostream>
#include "Mob.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"

Mob::Mob()
{
}

Mob::Mob(unsigned int _id, std::string const& _name, int hp, int damage, int type)
  : Behaviour(_id, _name), _hp(hp), _damage(damage), _type(type)
{
  _direction = 1;
}

Mob::Mob(Mob const& other) : Behaviour(other)
{
  _enabled = other._enabled;
    _hp = other._hp;
    _damage = other._damage;
    _direction = other._direction;
    _type = other._type;
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
}

namespace std
{
    template<>
    void swap<Mob>(Mob& a, Mob& b)
    {
        a.swap(b);
    }
}

int	Mob::getHp() const
{
  return _hp;
}

int	Mob::getDamage() const
{
  return _damage;
}

void		Mob::move(Transform & transform)
{
  float		speed = static_cast<float>(3.0);

  _graphicHeight = static_cast<GameObject *>(parent())->renderer().getRect().h;
  if (!_enabled)
    return ;
  switch (_type)
    {
    case 0:
      if (transform.getPosition().Y() <= 0)
	_direction = 1;
      else if (transform.getPosition().Y() >= Renderer::height - _graphicHeight)
	_direction = -1;
      transform.getPosition().setY((transform.getPosition().Y() + _direction * speed));
      break;
    case 1:
      if (transform.getPosition().Y() >= Renderer::height - _graphicHeight)
	_type = 2;
      _direction = -1;
      transform.getPosition().setY((transform.getPosition().Y() + _direction * -1 * speed));
      transform.getPosition().setX((transform.getPosition().X() + _direction * speed * 3 / 4));
      break;
    case 2:
      if (transform.getPosition().Y() <= 0)
	_type = 1;
      _direction = -1;
      transform.getPosition().setY((transform.getPosition().Y() + _direction * speed));
      transform.getPosition().setX((transform.getPosition().X() + _direction * speed * 3 / 4));
      break;
    case 3:
      _direction = -1;
      transform.getPosition().setX((transform.getPosition().X() + _direction * speed));
    default:
      _type = 3;
      break;
    }
  std::cout << transform.getPosition().toString() << std::endl;
}

void		Mob::update(double)
{
  Transform	&transform = static_cast<GameObject *>(parent())->transform();

  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move(transform);
}
