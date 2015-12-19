#include <iostream>
#include "Mob.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"

Mob::Mob()
{
}

Mob::Mob(unsigned int _id, std::string const& _name, int hp, int damage)
  : Behaviour(_id, _name), _hp(hp), _damage(damage)
{
  _direction = 1;
}

Mob::Mob(Mob const& other) : Behaviour(other)
{
    _hp = other._hp;
    _damage = other._damage;
    _direction = other._direction;
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
  float		speed = static_cast<float>(2.0);
  Transform	&transform = static_cast<GameObject *>(parent())->transform();

  if (!_enabled)
    return ;
  /* Mob 1 */
  // if (transform.getPosition().Y() <= 0)
  //   _direction = 1;
  // else if (transform.getPosition().Y() >= 690)
  //   _direction = -1;
  // transform.getPosition().setY((transform.getPosition().Y() + _direction * speed));

  /* Mob 2 */
  // ne pas oublier de set le Y
  // _direction = -1;
  // transform.getPosition().setX((transform.getPosition().X() + _direction * speed));

  /* Mob 3 */
  // ne pas oublier de set le X et le Y de départ
  _direction = -1;
  transform.getPosition().setY((transform.getPosition().Y() + _direction * -1 * speed));
  transform.getPosition().setX((transform.getPosition().X() + _direction * speed));

  /* Mob 4 */
  // ne pas oublier de set le X et le Y de départ
  // _direction = -1;
  // transform.getPosition().setY((transform.getPosition().Y() + _direction * speed));
  // transform.getPosition().setX((transform.getPosition().X() + _direction * speed));
}

void	Mob::update(double)
{
  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move();
}
