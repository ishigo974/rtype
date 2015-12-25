//
// Created by fourdr_b on 24/12/15.
//

#include <AudioEffect.hpp>
#include <Mob.hpp>
#include "NetPlayerComp.hpp"
#include "Collider.hpp"

NetPlayerComp::NetPlayerComp() : _transform(nullptr)
{ }

NetPlayerComp::NetPlayerComp(unsigned int id, std::string const& name, EntityManager *em, int hp, int dmg)
        : Behaviour(id, name), _hp(hp), _damage(dmg), _em(em), _transform(nullptr)
{ }

NetPlayerComp::NetPlayerComp(NetPlayerComp& o) : Behaviour(o)
{
    _parent   = o._parent;
    _hp       = o._hp;
    _damage   = o._damage;
    _multiple = o._multiple;

    _bullets       = o._bullets;
    _activeBullets = o._activeBullets;

    _em        = o._em;
    _transform = o._transform;
    _shotTime  = o._shotTime;
}

NetPlayerComp::NetPlayerComp(NetPlayerComp&& o) : NetPlayerComp(o)
{
    swap(o);
}

NetPlayerComp& NetPlayerComp::operator=(NetPlayerComp& o)
{
    swap(o);

    return (*this);
}

NetPlayerComp::~NetPlayerComp()
{

}

void NetPlayerComp::swap(NetPlayerComp& o)
{
    using std::swap;

    swap(_parent, o._parent);
    swap(_hp, o._hp);
    swap(_damage, o._damage);
    swap(_multiple, o._multiple);
    swap(_bullets, o._bullets);
    swap(_activeBullets, o._activeBullets);
    swap(_em, o._em);
    swap(_transform, o._transform);
    swap(_shotTime, o._shotTime);
}

namespace std
{
    template<>
    inline void swap<NetPlayerComp>(NetPlayerComp& a, NetPlayerComp& b)
    {
        a.swap(b);
    }
}

void NetPlayerComp::move(double elapsedTime)
{
    float speed = 1.25f;

    if (_multiple)
    {
        _multiple = false;
        speed     = speed * 3 / 4;
    }
    if (_udp->sizeRecv() >= 2)
    {
        _multiple = true;
        speed     = speed * 3 / 4;
    }

    auto tmp = _udp->popReceive(); // TODO add verif

    switch (tmp)
    {
        case UDPView::Action::MOVE_UP:
            _transform->getPosition().setY(_transform->getPosition().Y() - speed * static_cast<float>(elapsedTime));
            break;
        case UDPView::Action::MOVE_DOWN:
            _transform->getPosition().setY(_transform->getPosition().Y() + speed * static_cast<float>(elapsedTime));
            break;
        case UDPView::Action::MOVE_LEFT:
            _transform->getPosition().setX(_transform->getPosition().X() - speed * static_cast<float>(elapsedTime));
            break;
        case UDPView::Action::MOVE_RIGHT:
            _transform->getPosition().setX(_transform->getPosition().X() + speed * static_cast<float>(elapsedTime));
            break;
        default:
            break;
    }
}

void		NetPlayerComp::checkDeath()
{
    if (_hp <= 0)
    {
        std::cout << "Player Mort" << std::endl;
        _enabled = false;
        _parent->setVisible(false);
        _parent->getComponent<Collider>()->setEnabled(false);
    }
}

void	NetPlayerComp::shoot()
{
    BulletObject *bullet = _bullets->create("Bullet", 12);
    bullet->init();
    _activeBullets.push_back(bullet);
    Bullet *b = bullet->getComponent<Bullet>();
    b->setX(_transform->getPosition().X() + _parent->getComponent<SpriteRenderer>()->getRect().w);
    b->setY(_transform->getPosition().Y());
    _shotTime = 0;
    std::vector<Object *>sound = _em->getByMask(SoundMask);
    for (auto play : sound)
    {
        static_cast<GameObject *>(play)->getComponent<AudioEffect>()
                                       ->setSoundToPlay("../res/laser1.wav");
    }
}

void	NetPlayerComp::checkAvailableBullets()
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

void		NetPlayerComp::init()
{
    _parent = static_cast<GameObject *>(parent());
    _bullets = new ObjectPool<BulletObject, Bullet>("Bullet", 12, _em);

    _udp = _parent->getComponent<UDPView>();
}

void		NetPlayerComp::update(double elapsedtime)
{
    if (!_transform)
        _transform = _parent->getComponent<Transform>();
    checkDeath();
    _shotTime += elapsedtime;
    checkAvailableBullets();
    while (_udp->sizeRecv() > 0)
    {
        auto tmp = _udp->popReceive();

        if (tmp == UDPView::Action::SHOT_START && _shotTime >= 80)
            this->shoot();
        else
            this->move(elapsedtime);
    }
}

bool NetPlayerComp::handleMessage(Collider *o)
{
    GameObject	*otherParent = static_cast<GameObject *>(o->parent());

    if (otherParent->getComponent<Mob>() != nullptr)
        _hp -= 1;
    return (true);
}

int NetPlayerComp::getHp() const
{
    return (_hp);
}
