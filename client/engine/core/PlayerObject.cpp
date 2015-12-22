#include "PlayerObject.hpp"
#include "Player.hpp"

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
  std::stringstream ss;

  ss << "PlayerObject {"
     << "\n\tid: " << _id
     << "\n\tname: " << _name
     << "\n\tlayer: " << _layer
     << "\n\tnbComponents: " << _components.size()
     << "\n\tTransform: " << getComponent<Transform>()->toString()
     << "\n}" << std::endl;

  return (ss.str());
}

void	PlayerObject::init()
{
  _entityManager->attachComponent<SpriteRenderer>(this, "Player", "player", gu::Rect<int>(67, 3, 32, 12));
  _entityManager->attachComponent<Player>(this, "Player", _entityManager);
  this->getComponent<Player>()->init();
  _entityManager->attachComponent<Collider>(this, "collider", 32, 12);

  Transform *t = this->getComponent<Transform>();
  t->getPosition().setX(100);
  t->getPosition().setY(300);
  this->getComponent<Player>()->setEnabled(true);
}
