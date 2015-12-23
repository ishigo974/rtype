#include "MobObject.hpp"
#include "Mob.hpp"
#include "Collider.hpp"

MobObject::MobObject()
{ }

MobObject::MobObject(unsigned int _id, std::string const& _name,
                           int _layer, EntityManager *manager)
  : GameObject(_id, _name, _layer), _entityManager(manager)
{
}

MobObject::MobObject(MobObject const& other) : GameObject(other)
{
    _layer = other.getLayer();
    _entityManager = other._entityManager;
}

MobObject::MobObject(MobObject&& other) : MobObject(other)
{
    swap(other);
}

MobObject& MobObject::operator=(MobObject other)
{
    swap(other);

    return (*this);
}

bool MobObject::operator==(MobObject const& other)
{
    return (GameObject::operator==(other) &&
            _layer == other.getLayer());
}

bool MobObject::operator!=(MobObject const& other)
{
    return (!MobObject::operator==(other));
}

void MobObject::swap(MobObject& other)
{
    using std::swap;

    swap(_layer, other._layer);
    swap(_entityManager, other._entityManager);
}

namespace std
{
    template<>
    inline void swap<MobObject>(MobObject& a, MobObject& b)
    {
        a.swap(b);
    }
}

MobObject::~MobObject()
{
    _components.clear();
}

std::string	MobObject::toString() const
{
    std::stringstream ss;

    ss << "MobObject {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tlayer: " << _layer
    << "\n\tnbComponents: " << _components.size()
    << "\n\tTransform: " << getComponent<Transform>()->toString()
    << "\n}" << std::endl;

    return (ss.str());
}

void	MobObject::deleteObject()
{
    Mob *b = this->getComponent<Mob>();
    // b->setDirection(Bullet::Direction::DEFAULT);
    // b->setEnabled(false);
    // b->setAvailable(true);
    // setVisible(false);
    // b->setDamage(0);
    // b->setHp(0);
    // getComponent<Collider>()->setEnabled(false);
    // TODO
}

void    MobObject::init()
{
    // _entityManager->attachComponent<SpriteRenderer>(this, "Bullet", "r-typesheet1",
    //                                                 gu::Rect<int>(249, 105, 16, 8));
    // _entityManager->attachComponent<Bullet>(this, "Bullet");
    // _entityManager->attachComponent<Collider>(this, "Bullet collider", 16, 8);
}

void	MobObject::reset()
{
    // Bullet *b = this->getComponent<Bullet>();
    // b->init();
    // b->setDirection(Bullet::Direction::RIGHT);
    // b->setEnabled(true);
    // b->setAvailable(false);
    // setVisible(true);
    // b->setDamage(1);
    // b->setHp(1);
    // getComponent<Collider>()->setEnabled(true);
}
