#include <iostream>
#include "Transform.hpp"
#include "GameObject.hpp"
#include "MobSpawner.hpp"
#include "ObjectPool.hpp"
#include "MobObject.hpp"

MobSpawner::MobSpawner()
{
}

MobSpawner::MobSpawner(unsigned int _id, std::string const& _name, EntityManager *manager,
                       RTypeGame::MobTypeMap *mobTypes) :
    Behaviour(_id, _name), _entityManager(manager), _mobTypes(mobTypes)
{
}

MobSpawner::MobSpawner(MobSpawner const& other) : Behaviour(other)
{
    _entityManager = other._entityManager;
    _mobs = other._mobs;
    _activeMobs = other._activeMobs;
    _udpView = other._udpView;
    _parent = other._parent;
}

MobSpawner::MobSpawner(MobSpawner&& other) : MobSpawner(other)
{
    swap(other);
}

MobSpawner& MobSpawner::operator=(MobSpawner other)
{
    swap(other);

    return (*this);
}

MobSpawner::~MobSpawner()
{
    if (_mobs)
        delete _mobs;
}

bool MobSpawner::operator==(MobSpawner const& other)
{
    return (Behaviour::operator==(other));
}

bool MobSpawner::operator!=(MobSpawner const& other)
{
    return (!MobSpawner::operator==(other));
}

void MobSpawner::swap(MobSpawner& other)
{
    using std::swap;

    swap(_mobs, other._mobs);
    swap(_entityManager, other._entityManager);
    swap(_activeMobs, other._activeMobs);
    swap(_udpView, other._udpView);
    swap(_parent,  other._parent);
}

namespace std
{
    template<>
    inline void swap<MobSpawner>(MobSpawner& a, MobSpawner& b)
    {
        a.swap(b);
    }
}

RTypes::my_uint16_t     MobSpawner::getMask() const
{
    return Mask;
}

void	MobSpawner::spawnMob(unsigned int id)
{
    // std::cout << "inactive mobs => " << _mobs->_objects.size() << std::endl;
    // std::cout << "Active mobs => " << _activeMobs.size() << std::endl;

    MobObject *mob = _mobs->create("Mob", 12);
    mob->init(_mobTypes->at(id).get());
    _activeMobs.push_back(mob);
    Mob *m = mob->getComponent<Mob>();
    m->setX(500); // TODO mettre la position donnée dans le fichier _transform->getPosition().X() + _parent->getComponent<SpriteRenderer>()->getRect().w);
    // m->setY(_transform->getPosition().Y());
}

void                      MobSpawner::init()
{
    _mobs = new ObjectPool<MobObject, Mob>("Mob", 12, _entityManager);
    MobObject *mob = _mobs->create("Mob", 12);
    mob->create();
    _parent = static_cast<GameObject *>(parent());
    _udpView = _parent->getComponent<UDPView>();
}

void		              MobSpawner::update(double)
{
    RType::InGameEvent    event;

    for (auto it = _activeMobs.begin(); it != _activeMobs.end(); ++it)
    {
        if ((*it)->getComponent<Mob>()->getAvailable())
        {
            _mobs->deleteObject(*it);
            _activeMobs.erase(it);
            break;
        }
    }
    if (_udpView->sizeRecv())
    {
        std::cout << _udpView->sizeRecv() << std::endl;
        event = _udpView->popReceive();
    }
    try {
        spawnMob(event.get<uint8_t>("mob_id"));
    }
    catch (Exception::ValueError const & e)
    {
    }
}
