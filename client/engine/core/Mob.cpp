#include <iostream>
#include "Mob.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"

Mob::Mob()
{
}

Mob::Mob(unsigned int _id, std::string const& _name, int hp, int damage, Object* parent)
  : Behaviour(_id, _name, parent), _hp(hp), _damage(damage)
{
}

Mob::Mob(Mob const& other) : Behaviour(other)
{
    _hp = other.getHp();
    _damage = other.getDamage();
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

void		Mob::move()
{
  GameObject	*parent;
  Transform	*transform;

  if (!_enabled)
    return ;
  parent = static_cast<GameObject *>(this->_parent);
  if (parent == nullptr)
    return ;
  transform = parent->getComponent<Transform>();
  if (transform == nullptr)
    return ;
  if (transform->getPosition().Y() == 0)
    transform->getPosition().setY(200);
  else if (transform->getPosition().Y() == 200)
    transform->getPosition().setY(0);
  std::cout << "Mob " << transform->getPosition().toString() << std::endl;
}

void	Mob::update(double elapsedTime)
{
  (void)elapsedTime;
  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move();
}
