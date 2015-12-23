#include <iostream>
#include "Transform.hpp"
#include "GameObject.hpp"
#include "ObjectPool.hpp"

MobSpawner::MobSpawner()
{
}

MobSpawner::MobSpawner(unsigned int _id, std::string const& _name, EntityManager *manager) :
    Behaviour(_id, _name), _entityManager(manager), _mobs("Bullet", 12, _entityManager);
{
}

MobSpawner::MobSpawner(MobSpawner const& other) : Behaviour(other)
{
    _entityManager = other._entityManager;
    _mobs = other._mobs;
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
    if (_bullets)
        delete _bullets;
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

    swap(_enabled, other._enabled);
    swap(_hp, other._hp);
    swap(_action, other._action);
    swap(_multiple, other._multiple);
    swap(_entityManager, other._entityManager);
    swap(_bullets, other._bullets);
    swap(_activeBullets, other._activeBullets);
    swap(_transform, other._transform);
    swap(_damage, other._damage);
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

std::string MobSpawner::toString() const
{
    std::stringstream ss;

    ss << "MobSpawner {"
    << "\n\thp: " << _hp
    << "\n\tdamage: " << _damage
    << "\n\tenabled: " << _enabled;
    if (_transform)
    ss << "\n\t" << _transform->toString();
    ss << "\n}" << std::endl;

    return (ss.str());
}

int	MobSpawner::getDamage() const
{
    return _damage;
}

int	MobSpawner::getHp() const
{
    return _hp;
}

void	MobSpawner::setAction(ACommand::Action action)
{
    _action.push(action);
}

void		MobSpawner::move(double elapsedtime)
{
    float		speed = 0.75f;

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
            _transform->getPosition().setY(_transform->getPosition().Y() - speed * elapsedtime);
            break;
        case ACommand::DOWN:
            _transform->getPosition().setY(_transform->getPosition().Y() + speed * elapsedtime);
            break;
        case ACommand::LEFT:
            _transform->getPosition().setX(_transform->getPosition().X() - speed * elapsedtime);
            break;
        case ACommand::RIGHT:
            _transform->getPosition().setX(_transform->getPosition().X() + speed * elapsedtime);
            break;
        default:
            break;
    }
}

std::vector<BulletObject *>	MobSpawner::getActiveBullets() const
{
    return _activeBullets;
}

void		MobSpawner::checkDeath()
{
    if (_hp <= 0)
    {
        std::cout << "MobSpawner Mort" << std::endl;
        _enabled = false;
        _parent->setVisible(false);
        _parent->getComponent<Collider>()->setEnabled(false);
    }
}

void	MobSpawner::shoot()
{

    BulletObject *bullet = _bullets->create("Bullet", 12);
    _activeBullets.push_back(bullet);
    Bullet *b = bullet->getComponent<Bullet>();
    b->setX(_transform->getPosition().X() + _parent->getComponent<SpriteRenderer>()->getRect().w);
    b->setY(_transform->getPosition().Y());
    _shotTime = 0;
    std::vector<Object *>sound = _entityManager->getByMask(SoundMask);
    for (auto play : sound)
    {
        static_cast<GameObject *>(play)->getComponent<AudioEffect>()
                                       ->setSoundToPlay("../res/laser1.wav");
    }
}

void	MobSpawner::checkAvailableBullets()
{
    for (auto it = _activeBullets.begin(); it != _activeBullets.end(); ++it)
    {
        if ((*it)->getComponent<Bullet>()->getAvailable())
        {
            _bullets->deleteObject(*it);
            _activeBullets.erase(it);
            break;
        }
    }
}

void		MobSpawner::init()
{
}

void		MobSpawner::update(double elapsedtime)
{
    _parent = static_cast<GameObject *>(parent());
    if (!_transform)
        _transform = _parent->getComponent<Transform>();
    checkDeath();
    _shotTime += elapsedtime;
    checkAvailableBullets();
    while (_action.size() > 0)
    {
        if (_action.front() == ACommand::SHOOT && _shotTime >= 200)
            this->shoot();
        else
            this->move(elapsedtime);
        _action.pop();
    }
    // TODO enlever ? _parent->getComponent<Collider>()->fixedUpdate(elapsedtime);
    // TODO remove debug comments
    // std::cout << "ACTIVE BULLETS => " << _activeBullets.size() << std::endl;
    // std::cout << "INACTIVE BULLETS => " << _bullets->_objects.size() << std::endl;
}

bool MobSpawner::handleMessage(Collider *o)
{
    GameObject	*otherParent = static_cast<GameObject *>(o->parent());

    if (otherParent->getComponent<Mob>() != nullptr)
        _hp -= 1;
    return (true);
}
