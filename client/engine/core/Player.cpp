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
  _bullets = new ObjectPool<BulletObject, Bullet>(_entityManager);
}

Player::Player(Player const& other) : Behaviour(other)
{
    _hp = other._hp;
    _action = other._action;
    _multiple = other._multiple;
    _entityManager = other._entityManager;
    _bullets = other._bullets;
    _activeBullets = other._activeBullets;
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
    swap(_bullets, other._bullets);
    swap(_activeBullets, other._activeBullets);
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
       << "\n\tenabled: " << _enabled
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
  float		speed = 7.5f;

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

std::vector<BulletObject *>	Player::getActiveBullets() const
{
  return _activeBullets;
}

void		Player::update(double elapsedtime)
{
  Transform	&transform = static_cast<GameObject *>(parent())->transform();

  _time += elapsedtime;
  // std::cout << _time << std::endl;
  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  for (auto it = _activeBullets.begin(); it != _activeBullets.end(); ++it)
    {
      if ((*it)->getComponent<Bullet>()->getAvailable())
  	{
  	  _bullets->deleteObject(*it);
  	  _activeBullets.erase(it);
  	  break;
  	}
    }
  while (_action.size() > 0)
    {
      if (_action.front() == ACommand::SHOOT && _shotTime >= 0.0001)
      	{
      	  BulletObject *bullet = _bullets->create("Bullet", 12);
      	  _activeBullets.push_back(bullet);
      	  Bullet *b = bullet->getComponent<Bullet>();
      	  b->setX(transform.getPosition().X());
      	  b->setY(transform.getPosition().Y());
	  _time = 0;
	}
      else
	this->move(transform);
      _action.pop();
    }
  // std::cout << toString() << std::endl;
  // std::cout << "ACTIVE BULLETS => " << _activeBullets.size() << std::endl;
  // std::cout << "INACTIVE BULLETS => " << _bullets->_objects.size() << std::endl;
}
