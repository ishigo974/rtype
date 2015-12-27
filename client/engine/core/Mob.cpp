#include <iostream>
#include "Mob.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Collider.hpp"
#include "Player.hpp"
#include "Animation.hpp"
#include "AudioEffect.hpp"

/*
** Constructor/Destructor
*/
Mob::Mob() :
    _id(0), _name(""), _lives(0),
    _scoreValue(0), _spriteFilePath(""),
    _movePattern(), _transform(nullptr),
    _state(1), _parent(nullptr), _entityId(0)
{
}

Mob::Mob(unsigned int id, std::string const& name, EntityManager* em, RType::MobType::IMobType const*) :
    Behaviour(id, name), _lives(0),
    _scoreValue(0), _spriteFilePath(""),
    _movePattern(), _transform(nullptr),
    _state(1), _parent(nullptr),
    _em(em), _entityId(0)
{
}

Mob::~Mob()
{
}

/*
** Copy and swap
*/
Mob::Mob(Mob const& other) :
    Behaviour(other), _id(other._id), _name(other._name), _lives(other._lives),
    _scoreValue(other._scoreValue), _spriteFilePath(other._spriteFilePath),
    _movePattern(other._movePattern), _transform(other._transform),
    _state(other._state), _parent(other._parent), _em(other._em),
    _entityId(other._entityId)
{
}

Mob::Mob(Mob&& other) : Mob(other)
{
    swap(other);
}

Mob& Mob::operator=(Mob other)
{
    swap(other);
    return (*this);
}

/*
** Overloaded operators
*/
bool Mob::operator==(Mob const& other)
{
    return (Behaviour::operator==(other));
}

bool Mob::operator!=(Mob const& other)
{
    return (!Mob::operator==(other));
}

RTypes::my_uint16_t     Mob::getMask() const
{
    return Mask;
}

/*
** Public member functions
*/
void        Mob::init(RType::MobType::IMobType const* type)
{
    initTransform();
    if (!_parent)
        _parent = static_cast<GameObject *>(parent());
    if (!_transform)
        _transform = static_cast<GameObject *>(parent())->getComponent<Transform>();
    _id = type->getId();
    _name = type->getName();
    _lives = type->getNbLives();
    _scoreValue = type->getScoreValue();
    _spriteFilePath = type->getSpriteFilePath();
    _movePattern = type->getMovePattern();
}

void        Mob::initTransform()
{
    _parent = static_cast<GameObject *>(parent());
    _transform = _parent->getComponent<Transform>();
}

bool        Mob::handleMessage(Collider *o)
{
    GameObject	*otherParent = static_cast<GameObject *>(o->parent());

    if (((otherParent->getComponent<Player>() != nullptr
        || otherParent->getComponent<Bullet>() != nullptr)
        && otherParent->getComponent<Mob>() == nullptr) && _lives > 0)
        _lives -= 1;
    if (_lives == 0)
    {
              std::vector<Object *> sound = _em->getByMask(SoundMask);
        for (auto             play : sound)
        {
            static_cast<GameObject *>(play)->getComponent<AudioEffect>()
                                           ->setSoundToPlay("../res/mobDeath.wav");
        }
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

void		Mob::setX(float x)
{
    _transform->getPosition().setX(x);
}

void		Mob::setY(float y)
{
    _transform->getPosition().setY(y);
}

void        Mob::setEntityId(unsigned int id)
{
    _entityId = id;
}

void		Mob::move(double elapsedTime)
{
    cu::Position    pos = _movePattern(_transform->getPosition(), elapsedTime,
                                       _state);

    _transform->getPosition().setX(pos.X());
    _transform->getPosition().setY(pos.Y());
    std::cout << pos.X() << " " << pos.Y() << std::endl;
}

void		Mob::update(double)
{
    if (_lives <= 0)
    {
            if (!_parent->getComponent<Animation>()->isPlaying())
            {
                _available = true;
                _enabled = false;
                _parent->setVisible(false);
                _parent->getComponent<Collider>()->setEnabled(false);
            }
    }
    if (_transform->getPosition().X() > Renderer::width + 1000
        || _transform->getPosition().X() < -1000
        || _transform->getPosition().Y() > Renderer::height + 1000
        || _transform->getPosition().Y() < -1000)
        _lives = 0;
}

void            Mob::addLives(unsigned int nb)
{
    _lives += nb;
}

void            Mob::removeLives(unsigned int nb)
{
    if (nb > _lives)
        _lives = 0;
    else
        _lives -= nb;
}

bool                    Mob::getAvailable() const
{
    return _available;
}

void                    Mob::setAvailable(bool a)
{
    _available = a;
}
void                    Mob::setMovePattern(RType::MobType::MovePattern const & movePattern)
{
    _movePattern = movePattern;
}

void                    Mob::setSpriteFilePath(std::string const & spriteFilePath)
{
    _spriteFilePath = spriteFilePath;
}

void                    Mob::setName(std::string const & name)
{
    _name = name;
}

void                    Mob::setScoreValue(unsigned int scoreValue)
{
    _scoreValue = scoreValue;
}

void                    Mob::setLives(unsigned int lives)
{
    _lives = lives;
}

unsigned int            Mob::getMobId() const
{
    return _id;
}

std::string const&      Mob::getMobName() const
{
    return _name;
}

unsigned int            Mob::getLives() const
{
    return _lives;
}

unsigned int            Mob::getScoreValue() const
{
    return _scoreValue;
}

std::string const&      Mob::getSpriteFilePath() const
{
    return _spriteFilePath;
}

unsigned int            Mob::getEntityId() const
{
    return _entityId;
}

RType::MobType::MovePattern const&      Mob::getMovePattern() const
{
    return _movePattern;
}

int&                    Mob::getState()
{
    return _state;
}

std::string Mob::toString() const
{
    return "Component::Mob {"
           "\n\t_id: " + std::to_string(_id) +
           "\n\t_name: " + _name +
           "\n\t_lives: " + std::to_string(_lives) +
           "\n\t_scoreValue: " + std::to_string(_scoreValue) +
           "\n\t_spriteFilePath: " + _spriteFilePath +
           "\n}\n";
}

void Mob::swap(Mob& other)
{
    using std::swap;

    swap(_id, other._id);
    swap(_name, other._name);
    swap(_lives, other._lives);
    swap(_scoreValue, other._scoreValue);
    swap(_spriteFilePath, other._spriteFilePath);
    swap(_movePattern, other._movePattern);
    swap(_transform, other._transform);
    swap(_state, other._state);
    swap(_parent, other._parent);
    swap(_em, other._em);
    swap(_entityId, other._entityId);
}

namespace std
{
    template<>
    inline void swap<Mob>(Mob& a, Mob& b)
    {
        a.swap(b);
    }
}
