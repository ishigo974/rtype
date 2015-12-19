#include <iostream>
#include "Player.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Ball.hpp"

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
}

namespace std
{
    template<>
    void swap<Player>(Player& a, Player& b)
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
  float		speed = static_cast<float>(10.0);

  if (!_enabled)
    return ;
  
  switch (_action.front())
    {
    case ACommand::UP:
      transform.getPosition().setY((transform.getPosition().Y() - speed));
      break;
    case ACommand::DOWN:
      transform.getPosition().setY((transform.getPosition().Y() + speed));
      break;
    case ACommand::LEFT:
      transform.getPosition().setX((transform.getPosition().X() - speed));
      break;
    case ACommand::RIGHT:
      transform.getPosition().setX((transform.getPosition().X() + speed));
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
	  Ball *ball = static_cast<GameObject *>(parent())->getComponent<Ball>();
	  if (ball == nullptr)
	    {
	      std::cout << "Ball failed" << std::endl;
	      _action.pop();
	      break;
	    }
	  ball->setX(transform.getPosition().X());
	  ball->setY(transform.getPosition().Y());
	  ball->setDirection(Ball::Direction::RIGHT);
	  // std::cout << "SHOOT" << std::endl;
	}
      else
	this->move(transform);
      _action.pop();
    }
}
