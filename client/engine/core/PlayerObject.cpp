#include "PlayerObject.hpp"
#include "Player.hpp"
#include "Animation.hpp"
#include "GameConfig.hpp"

PlayerObject::PlayerObject()
{ }

PlayerObject::PlayerObject(unsigned int _id, std::string const& _name, int _layer, EntityManager *manager)
  : GameObject(_id, _name, _layer), _entityManager(manager)
{
}

PlayerObject::PlayerObject(PlayerObject const& other) : GameObject(other)
{
    _layer = other.getLayer();
    _entityManager = other._entityManager;
}

PlayerObject::PlayerObject(PlayerObject&& other) : PlayerObject(other)
{
    swap(other);
}

PlayerObject& PlayerObject::operator=(PlayerObject other)
{
    swap(other);

    return (*this);
}

bool PlayerObject::operator==(PlayerObject const& other)
{
    return (GameObject::operator==(other) &&
            _layer == other.getLayer());
}

bool PlayerObject::operator!=(PlayerObject const& other)
{
    return (!PlayerObject::operator==(other));
}

void PlayerObject::swap(PlayerObject& other)
{
    using std::swap;

    swap(_layer, other._layer);
    swap(_entityManager, other._entityManager);
}

namespace std
{
    template<>
    inline void swap<PlayerObject>(PlayerObject& a, PlayerObject& b)
    {
        a.swap(b);
    }
}

PlayerObject::~PlayerObject()
{
    _components.clear();
}

std::string	PlayerObject::toString() const
{
  std::string ss;

  ss = "PlayerObject {";
  ss += "\n\tid: ";
  ss += _id;
  ss += "\n\tname: ";
  ss += _name;
  ss += "\n\tlayer: ";
  ss += _layer;
  ss += "\n\tnbComponents: ";
  ss += _components.size();
  ss += "\n\tTransform: " + getComponent<Transform>()->toString();
  ss += "\n}\n";

  return (ss);
}

void	PlayerObject::init()
{
  _entityManager->attachComponent<SpriteRenderer>(this, "Player", "player", gu::Rect<int>(67, 3, 32, 12));
  _entityManager->attachComponent<Player>(this, "Player", _entityManager);
  this->getComponent<Player>()->init();
  _entityManager->attachComponent<Collider>(this, "collider", RType::Ship::cWidth, RType::Ship::cHeight);
  _entityManager->attachComponent<Animation>(this, "AN", 1.0, 1.0, false);
  getComponent<Animation>()->stop();

  Transform *t = this->getComponent<Transform>();
  t->getPosition().setX(100);
  t->getPosition().setY(300);
  this->getComponent<Player>()->setEnabled(true);
}
