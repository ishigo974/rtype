#include <iostream>
#include "Ball.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"

Ball::Ball()
{
}

Ball::Ball(unsigned int _id, std::string const& _name, int hp, int damage)
  : Behaviour(_id, _name), _hp(hp), _damage(damage)
{
  _direction = Ball::Direction::DEFAULT;
}

Ball::Ball(Ball const& other) : Behaviour(other)
{
    _hp = other._hp;
    _damage = other._damage;
    _direction = other._direction;
}

Ball::Ball(Ball&& other) : Ball(other)
{
    swap(other);
}

Ball& Ball::operator=(Ball other)
{
    swap(other);

    return (*this);
}

Ball::~Ball()
{
}

bool Ball::operator==(Ball const& other)
{
    return (Behaviour::operator==(other));
}

bool Ball::operator!=(Ball const& other)
{
    return (!Ball::operator==(other));
}

void Ball::swap(Ball& other)
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
    inline void swap<Ball>(Ball& a, Ball& b)
    {
        a.swap(b);
    }
}

RTypes::my_uint16_t     Ball::getMask() const
{
  return Mask;
}

int	Ball::getHp() const
{
  return _hp;
}

int	Ball::getDamage() const
{
  return _damage;
}

void		Ball::setX(float x)
{
  Transform &_transform = static_cast<GameObject *>(parent())->transform();

  _transform.getPosition().setX(x);
}

void		Ball::setY(float y)
{
  Transform &_transform = static_cast<GameObject *>(parent())->transform();

  _transform.getPosition().setY(y);
}

void		Ball::setDirection(Ball::Direction d)
{
  _direction = d;
}

void		Ball::move(Transform & transform)
{
  float		speed = static_cast<float>(10.0);

  transform.getPosition().setX((transform.getPosition().X() + _direction * speed));
}

void		Ball::update(double)
{
  Transform	&transform = static_cast<GameObject *>(parent())->transform();

  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move(transform);
}
