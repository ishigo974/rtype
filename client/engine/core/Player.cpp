#include <iostream>
#include "Player.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"

Player::Player()
{
}

Player::Player(unsigned int _id, std::string const& _name, int hp, int damage, Object* parent)
  : Behaviour(_id, _name, parent), _hp(hp), _damage(damage)
{
  _action = ACommand::DEFAULT;
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
  _action = action;
}

void		Player::move(double elapsedTime)
{
  (void)elapsedTime;
  // static double	deltaPix = 0;
  // float		speed = 0.75f;
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

  switch (_action)
    {
    case ACommand::UP:
      transform->getPosition().setY((transform->getPosition().Y() - 1));
      _action = ACommand::DEFAULT;
      break;
    case ACommand::DOWN:
      transform->getPosition().setY((transform->getPosition().Y() + 1));
      _action = ACommand::DEFAULT;
      break;
    case ACommand::LEFT:
      transform->getPosition().setX((transform->getPosition().X() - 1));
      _action = ACommand::DEFAULT;
      break;
    case ACommand::RIGHT:
      transform->getPosition().setX((transform->getPosition().X() + 1));
      _action = ACommand::DEFAULT;
      break;
    default:
      break;
    }
  // std::cout << transform->getPosition().toString() << std::endl;
}

void	Player::update(double elapsedTime)
{
  (void)elapsedTime;
  if (_hp == 0)
    std::cout << "Mort" << std::endl;
  this->move(elapsedTime);
  if (_action == ACommand::SHOOT)
    std::cout << "SHOOT" << std::endl;
}
