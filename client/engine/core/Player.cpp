#include <iostream>
#include "Player.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Bullet.hpp"

Player::Player()
{
}

Player::Player(unsigned int _id, std::string const& _name, int hp, int damage)
  : Behaviour(_id, _name), _hp(hp), _damage(damage)
{
}

Player::Player(Player const& other) : Behaviour(other)
{
    _hp = other._hp;
    _damage = other._damage;
    _action = other._action;
    _multiple = other._multiple;
}

Player::Player(Player&& other) : Player(other)
{
    swap(other);
}

Player& Player::operator=(Player other)
{
    swap(other);

    return (*this);
}

Player::~Player()
{
}

bool Player::operator==(Player const& other)
{
    return (Behaviour::operator==(other));
}

bool Player::operator!=(Player const& other)
{
    return (!Player::operator==(other));
}

void Player::swap(Player& other)
{
    using std::swap;

    swap(_enabled, other._enabled);
    swap(_hp, other._hp);
    swap(_damage, other._damage);
    swap(_action, other._action);
    swap(_multiple, other._multiple);
}

namespace std
{
    template<>
    inline void swap<Player>(Player& a, Player& b)
    {
        a.swap(b);
    }
}

RTypes::my_uint16_t     Player::getMask() const
{
  return Mask;
}

int	Player::getHp() const
{
  return _hp;
}

int	Player::getDamage() const
{
  return _damage;
}

void	Player::setAction(ACommand::Action action)
{
  _action.push(action);
}

void		Player::move(Transform & transform)
{
  float		speed = 5.0f;

  if (!_enabled)
    return ;
  if (_multiple)
    {
      _multiple = false;
      speed = speed * 3 / 4;
    }
  if (_action.size() >= 2)
    {
      _multiple = true;
      speed = speed * 3 / 4;
    }
  switch (_action.front())
    {
    case ACommand::UP:
      transform.getPosition().setY(transform.getPosition().Y() - speed);
      break;
    case ACommand::DOWN:
      transform.getPosition().setY(transform.getPosition().Y() + speed);
      break;
    case ACommand::LEFT:
      transform.getPosition().setX(transform.getPosition().X() - speed);
      break;
    case ACommand::RIGHT:
      transform.getPosition().setX(transform.getPosition().X() + speed);
      break;
    default:
      break;
    }
}

void		Player::update(double)
{
  Transform	&transform = static_cast<GameObject *>(parent())->transform();

  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  while (_action.size() > 0)
    {
      if (_action.front() == ACommand::SHOOT)
	{
	  Bullet *bullet = static_cast<GameObject *>(parent())->getComponent<Bullet>();
	  if (bullet == nullptr)
	    {
	      std::cout << "Bullet failed" << std::endl;
	      _action.pop();
	      break;
	    }
	  bullet->setX(transform.getPosition().X());
	  bullet->setY(transform.getPosition().Y());
	  bullet->setDirection(Bullet::Direction::RIGHT);
	  // std::cout << "SHOOT" << std::endl;
	}
      else
	this->move(transform);
      _action.pop();
    }
}
