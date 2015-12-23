#include <iostream>
#include "Player.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Bullet.hpp"
#include "Mob.hpp"
#include "ObjectPool.hpp"
#include "AudioEffect.hpp"

Player::Player()
{
}

Player::Player(unsigned int _id, std::string const& _name, EntityManager *manager, int hp, int damage) :
    Behaviour(_id, _name), _hp(hp), _damage(damage), _entityManager(manager), _transform(0)
{
}

Player::Player(Player const& other) : Behaviour(other)
{
    _hp = other._hp;
    _action = other._action;
    _multiple = other._multiple;
    _entityManager = other._entityManager;
    _bullets = other._bullets;
    _transform = other._transform;
    _activeBullets = other._activeBullets;
    _damage = other._damage;
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
    std::stringstream ss;

    ss << "Player {"
    << "\n\thp: " << _hp
    << "\n\tdamage: " << _damage
    << "\n\tenabled: " << _enabled;
    if (_transform)
    ss << "\n\t" << _transform->toString();
    ss << "\n}" << std::endl;

    return (ss.str());
}

int	Player::getDamage() const
{
    return _damage;
}

int	Player::getHp() const
{
    return _hp;
}

void	Player::setAction(ACommand::Action action)
{
    _action.push(action);
}

void		Player::move(double elapsedtime)
{
    float		speed = 1.25f;

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
            _transform->getPosition().setY(_transform->getPosition().Y() - speed * static_cast<float>(elapsedtime));
            break;
        case ACommand::DOWN:
            _transform->getPosition().setY(_transform->getPosition().Y() + speed * static_cast<float>(elapsedtime));
            break;
        case ACommand::LEFT:
            _transform->getPosition().setX(_transform->getPosition().X() - speed * static_cast<float>(elapsedtime));
            break;
        case ACommand::RIGHT:
            _transform->getPosition().setX(_transform->getPosition().X() + speed * static_cast<float>(elapsedtime));
            break;
        default:
            break;
    }
}

const std::vector<BulletObject *>	&Player::getActiveBullets() const
{
    return _activeBullets;
}

void		Player::checkDeath()
{
    if (_hp <= 0)
    {
        std::cout << "Player Mort" << std::endl;
        _enabled = false;
        _parent->setVisible(false);
        _parent->getComponent<Collider>()->setEnabled(false);
    }
}

void	Player::shoot()
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

void	Player::checkAvailableBullets()
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

void		Player::init()
{
    _bullets = new ObjectPool<BulletObject, Bullet>("Bullet", 12, _entityManager);
}

void		Player::update(double elapsedtime)
{
    _parent = static_cast<GameObject *>(parent());
    if (!_transform)
        _transform = _parent->getComponent<Transform>();
    checkDeath();
    _shotTime += elapsedtime;
    checkAvailableBullets();
    while (_action.size() > 0)
    {
        if (_action.front() == ACommand::SHOOT && _shotTime >= 80)
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

bool Player::handleMessage(Collider *o)
{
    GameObject	*otherParent = static_cast<GameObject *>(o->parent());

    if (otherParent->getComponent<Mob>() != nullptr)
        _hp -= 1;
    return (true);
}
