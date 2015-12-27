#include "BulletObject.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Animation.hpp"
#include "GameConfig.hpp"

BulletObject::BulletObject()
{ }

BulletObject::BulletObject(unsigned int _id, std::string const& _name,
                           int _layer, EntityManager *manager)
  : GameObject(_id, _name, _layer), _entityManager(manager)
{
}

BulletObject::BulletObject(BulletObject const& other) : GameObject(other)
{
    _layer = other.getLayer();
    _entityManager = other._entityManager;
}

BulletObject::BulletObject(BulletObject&& other) : BulletObject(other)
{
    swap(other);
}

BulletObject& BulletObject::operator=(BulletObject other)
{
    swap(other);

    return (*this);
}

bool BulletObject::operator==(BulletObject const& other)
{
    return (GameObject::operator==(other) &&
            _layer == other.getLayer());
}

bool BulletObject::operator!=(BulletObject const& other)
{
    return (!BulletObject::operator==(other));
}

void BulletObject::swap(BulletObject& other)
{
    using std::swap;

    swap(_layer, other._layer);
    swap(_entityManager, other._entityManager);
}

namespace std
{
    template<>
    inline void swap<BulletObject>(BulletObject& a, BulletObject& b)
    {
        a.swap(b);
    }
}

BulletObject::~BulletObject()
{
    _components.clear();
}

std::string	BulletObject::toString() const
{
    std::string ss;

    ss = "BulletObject {";
    ss += "\n\tid: ";
    ss += _id;
    ss += "\n\tname: ";
    ss += _name;
    ss += "\n\tlayer: ";
    ss += _layer;
    ss += "\n\tnbComponents: ";
    ss += _components.size();
    ss += "\n\tTransform: ";
    ss += getComponent<Transform>()->toString();
    ss += "\n}\n";

    return (ss);
}

void	BulletObject::deleteObject()
{
    Bullet *b = this->getComponent<Bullet>();
    b->setDirection(Bullet::Direction::DEFAULT);
    b->setEnabled(false);
    b->setAvailable(true);
    setVisible(false);
    b->setDamage(0);
    b->setHp(0);
    getComponent<Collider>()->setEnabled(false);
    getComponent<SpriteRenderer>()->setPath("r-typesheet1");
    getComponent<SpriteRenderer>()->setRect(gu::Rect<int>(249, 105, 16, 8));
}

void    BulletObject::create()
{
    _entityManager->attachComponent<SpriteRenderer>(this, "Bullet", "r-typesheet1",
                                                    gu::Rect<int>(249, 105, 16, 8));
    _entityManager->attachComponent<Bullet>(this, "Bullet", _entityManager);
    _entityManager->attachComponent<Collider>(this, "Bullet collider", RType::Shot::width, RType::Shot::height);
    _entityManager->attachComponent<Animation>(this, "AN", 1.0, 1.0, false);
    getComponent<Animation>()->stop();
}

void	BulletObject::init()
{
    Bullet *b = this->getComponent<Bullet>();
    b->init();
    b->setDirection(Bullet::Direction::RIGHT);
    b->setEnabled(true);
    b->setAvailable(false);
    setVisible(true);
    b->setDamage(1);
    b->setHp(1);
    getComponent<Collider>()->setEnabled(true);
    getComponent<Animation>()->stop();
}
