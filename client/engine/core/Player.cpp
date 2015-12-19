#include <iostream>
#include "Player.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Bullet.hpp"
#include "ObjectPool.hpp"

Player::Player()
{
}

Player::Player(unsigned int _id, std::string const& _name, int hp)
  : Behaviour(_id, _name), _hp(hp)
{
}

Player::Player(Player const& other) : Behaviour(other)
{
    _hp = other._hp;
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

std::string Player::toString()
{
    std::stringstream ss;
    Transform	&transform = static_cast<GameObject *>(parent())->transform();

    ss << "Player {"
       << "\n\thp: " << _hp
       << "\n\t" << transform.toString()
       << "\n}" << std::endl;

    return (ss.str());
}

int	Player::getHp() const
{
  return _hp;
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
	  std::vector<Object *> bullets = EntityManager::getChildrenOf(static_cast<GameObject *>(parent()));
	  for (auto bullet : bullets)
	    {
	      Bullet *b = static_cast<GameObject *>(bullet)->getComponent<Bullet>();
	      b->setX(transform.getPosition().X());
	      b->setY(transform.getPosition().Y());
	      b->setDirection(Bullet::Direction::RIGHT);
	    }
	}
      else
	this->move(transform);
      _action.pop();
    }
}
