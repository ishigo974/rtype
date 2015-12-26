#include "MobObject.hpp"
#include "Mob.hpp"
#include "Collider.hpp"
#include "Animation.hpp"

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

void	MobObject::deleteObject()
{
    Mob *m = this->getComponent<Mob>();
    m->setLives(0);
    m->setScoreValue(0);
    // m->setSpriteFilePath("");
    // m->setMovePattern();
    m->setEnabled(false);
    m->setAvailable(true);
    setVisible(false);
    getComponent<Collider>()->setEnabled(false);
}

void    MobObject::create()
{
    _entityManager->attachComponent<SpriteRenderer>(this, "Mob", "mob",
                                                    gu::Rect<int>(1, 4, 32, 21));
    _entityManager->attachComponent<Mob>(this, "Mob");
    _entityManager->attachComponent<Collider>(this, "Mob collider", 32, 21);
    _entityManager->attachComponent<Animation>(this, "AN", 0, 0, true);
}

void	MobObject::init(RType::MobType::IMobType const* mobtype)
{
    Mob *m = this->getComponent<Mob>();
    m->init(mobtype);
    m->setEnabled(true);
    m->setAvailable(false);
    setVisible(true);
    getComponent<Collider>()->setEnabled(true);
    // _em->attachComponent<Animation>(this, "AN",
    //     _mobTypes->at(it->second.id).get()->getNumberFrames(),
    //     _mobTypes->at(it->second.id).get()->getDuration(),
    //     _mobTypes->at(it->second.id).get()->getLoop()
    // );
}
