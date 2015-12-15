#include <iostream>
#include "Ball.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"

Ball::Ball()
{
}

Ball::Ball(unsigned int _id, std::string const& _name, int hp, int damage, Object* parent)
  : Behaviour(_id, _name, parent), _hp(hp), _damage(damage)
{
}

Ball::Ball(Ball const& other) : Behaviour(other)
{
    _hp = other._hp;
    _damage = other._damage;
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
}

namespace std
{
    template<>
    inline void swap<Ball>(Ball& a, Ball& b)
    {
        a.swap(b);
    }
}

int	Ball::getHp() const
{
  return _hp;
}

int	Ball::getDamage() const
{
  return _damage;
}

void		Ball::move()
{
  GameObject	*parent;
  Transform	*transform;
  float		speed = static_cast<float>(1.0);

  if (!_enabled)
    return ;
  parent = static_cast<GameObject *>(this->_parent);
  if (parent == nullptr)
    return ;
  transform = parent->getComponent<Transform>();
  if (transform == nullptr)
    return ;
  transform->getPosition().setX((transform->getPosition().X() + speed));
}

void	Ball::update(double)
{
  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move();
}
