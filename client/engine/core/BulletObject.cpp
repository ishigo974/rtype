#include "BulletObject.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"

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
    std::stringstream ss;

    ss << "BulletObject {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tlayer: " << _layer
    << "\n\tnbComponents: " << _components.size()
    << "\n}" << std::endl;

    return (ss.str());
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
}

void    BulletObject::init()
{
    _entityManager->attachComponent<SpriteRenderer>(this, "Bullet", "r-typesheet1",
                                                    gu::Rect<int>(249, 105, 16, 8));
    _entityManager->attachComponent<Bullet>(this, "Bullet");
    _entityManager->attachComponent<Collider>(this, "Bullet collider", 16, 8);
}

void	BulletObject::reset()
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
}
