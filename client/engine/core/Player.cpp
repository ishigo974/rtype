#include <iostream>
#include "Player.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Bullet.hpp"
#include "Mob.hpp"
#include "ObjectPool.hpp"
#include "AudioEffect.hpp"
#include "GameConfig.hpp"
#include "Animation.hpp"

Player::Player()
{
}

Player::Player(unsigned int _id, std::string const& _name, EntityManager *manager, int hp, int damage) :
        Behaviour(_id, _name), _hp(hp), _damage(damage), _entityManager(manager), _transform(0)
{
}

Player::Player(Player const& other) : Behaviour(other)
{
    _hp            = other._hp;
    _action        = other._action;
    _multiple      = other._multiple;
    _entityManager = other._entityManager;
    _bullets       = other._bullets;
    _transform     = other._transform;
    _activeBullets = other._activeBullets;
    _damage        = other._damage;
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
    if (_bullets)
        delete _bullets;
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
    inline void swap<Player>(Player& a, Player& b)
    {
        a.swap(b);
    }
}

RTypes::my_uint16_t     Player::getMask() const
{
    return Mask;
}

std::string Player::toString() const
{
  std::string ss;
  
    ss += "Player {";
    ss += "\n\thp: ";
    ss += _hp;
    ss += "\n\tdamage: ";
    ss += _damage;
    ss += "\n\tenabled: ";
    ss += _enabled;
    if (_transform)
        ss += "\n\t" + _transform->toString();
    ss += "\n}\n";

    return (ss);
}

int    Player::getDamage() const
{
    return _damage;
}

int    Player::getHp() const
{
    return _hp;
}

void    Player::setAction(ACommand::Action action)
{
    _action.push(action);
}

void        Player::move(double elapsedtime)
{
    float  speed = RType::Speed::ship;
    double move;

    if (_hp <= 0)
        return ;

    move = speed * elapsedtime;
    if (_action.empty())
        return ;
    switch (_action.front())
    {
        case ACommand::UP:
            _transform->getPosition().setY(_transform->getPosition().Y() - move);
            break;
        case ACommand::DOWN:
            _transform->getPosition().setY(_transform->getPosition().Y() + move);
            break;
        case ACommand::LEFT:
            _transform->getPosition().setX(_transform->getPosition().X() - move);
            break;
        case ACommand::RIGHT:
            _transform->getPosition().setX(_transform->getPosition().X() + move);
            break;
        default:
            break;
    }
    std::cout << "Player move: " << _transform->getPosition().X() << " " << _transform->getPosition().Y() << std::endl;
}

const std::vector<BulletObject *>& Player::getActiveBullets() const
{
    return _activeBullets;
}

void        Player::checkDeath()
{
    if (_hp <= 0)
    {
        std::cout << "Player Mort" << std::endl;

        if (!_parent->getComponent<Animation>()->isPlaying())
        {
            _enabled = false;
            _parent->setVisible(false);
            _parent->getComponent<Collider>()->setEnabled(false);
        std::vector<Object *> sound = _entityManager->getByMask(SoundMask);
        for (auto             play : sound)
        {
            static_cast<GameObject *>(play)->getComponent<AudioEffect>()
                                           ->setSoundToPlay("../res/mobDeath.wav");
        }
        }
    }
}

void    Player::shoot()
{
    BulletObject *bullet = _bullets->create("Bullet", 12);
    bullet->init();
    _activeBullets.push_back(bullet);
    Bullet *b = bullet->getComponent<Bullet>();
    b->setX(_transform->getPosition().X() + RType::Ship::width);
    b->setY(_transform->getPosition().Y());
    _shotTime = 0;
    std::vector<Object *> sound = _entityManager->getByMask(SoundMask);
    for (auto             play : sound)
    {
        static_cast<GameObject *>(play)->getComponent<AudioEffect>()
                                       ->setSoundToPlay("../res/laser1.wav");
    }
}

void    Player::checkAvailableBullets()
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

void        Player::init()
{
    _bullets   = new ObjectPool<BulletObject, Bullet>("Bullet", 12, _entityManager);
    _parent    = static_cast<GameObject *>(parent());
    _transform = _parent->getComponent<Transform>();
}

void        Player::update(double elapsedtime)
{
    _parent        = static_cast<GameObject *>(parent());
    if (!_transform)
        _transform = _parent->getComponent<Transform>();

    checkDeath();
    _shotTime += elapsedtime;
    checkAvailableBullets();
    while (_action.size() > 0)
    {
        if (_action.front() == ACommand::SHOOT && _shotTime >= 150) // TODO synchro serv
            this->shoot();
        else
            this->move(elapsedtime);
        _action.pop();
    }
}

bool Player::handleMessage(Collider *o)
{
    GameObject *otherParent = static_cast<GameObject *>(o->parent());

    if (otherParent->getComponent<Mob>() != nullptr)
        _hp -= 1;
    if (_hp == 0)
    {
        _parent->getComponent<Collider>()->setEnabled(false);
        _parent->getComponent<SpriteRenderer>()->setPath("explosion");
        _parent->getComponent<SpriteRenderer>()->setRect(gu::Rect<int>(0, 0,
                                                                       32, 30));
        _parent->getComponent<Animation>()->setFrames(8);
        _parent->getComponent<Animation>()->setDuration(256.0);
        _parent->getComponent<Animation>()->setLoop(false);
        _parent->getComponent<Animation>()->play();
    }

    return (true);
}
