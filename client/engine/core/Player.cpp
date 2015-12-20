#include <iostream>
#include "Player.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Bullet.hpp"
#include "ObjectPool.hpp"

Player::Player()
{
}

Player::Player(unsigned int _id, std::string const& _name, EntityManager *manager, int hp)
  : Behaviour(_id, _name), _hp(hp), _entityManager(manager)
{
}

Player::Player(Player const& other) : Behaviour(other)
{
    _hp = other._hp;
    _action = other._action;
    _multiple = other._multiple;
    _entityManager = other._entityManager;
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
    swap(_entityManager, other._entityManager);
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

std::string Player::toString() const
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

void		Player::update(double elapsedtime)
{
  Transform	&transform = static_cast<GameObject *>(parent())->transform();

  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  for (auto it = _activeBullets.begin(); it != _activeBullets.end(); ++it)
    {
      if ((*it)->getAvailable())
	{
	  _bullets.deleteObject(*it);
	  (*it)->setAvailable(true);
	  (*it)->setEnabled(false);
	  _activeBullets.erase(it);
	  break;
	}
    }
  for (auto it = _activeBullets.begin(); it != _activeBullets.end(); ++it)
    (*it)->update(elapsedtime);
  while (_action.size() > 0)
    {
      if (_action.front() == ACommand::SHOOT && _activeBullets.size() < 30)
	{
	  Bullet *bullet = _bullets.create();
	  _activeBullets.push_back(bullet);
	  _entityManager->attachComponent<SpriteRenderer>(static_cast<GameObject *>(this->parent()), "Bullet", "r-typesheet1", gu::Rect<int>(249, 105, 16, 8));
	  bullet->setDirection(Bullet::RIGHT);
	  bullet->setEnabled(true);
	  bullet->setAvailable(false);
	  bullet->setX(transform.getPosition().X());
	  bullet->setY(transform.getPosition().Y());
	}
      else
	this->move(transform);
      _action.pop();
    }
  std::cout << "ACTIVE BULLETS => " << _activeBullets.size() << std::endl;
  std::cout << "INACTIVE BULLETS => " << _bullets._objects.size() << std::endl;
}
