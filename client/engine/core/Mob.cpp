#include <iostream>
#include "Mob.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Collider.hpp"
#include "Player.hpp"

/*
** Constructor/Destructor
*/
Mob::Mob() :
    _id(0), _name(""), _lives(0),
    _scoreValue(0), _spriteFilePath(""),
    _movePattern(), _transform(nullptr)
{
}

Mob::Mob(unsigned int id, std::string const& name,
         RType::MobType::IMobType const* mobtype) :
    Behaviour(id, name),
    _id(0), _name(""), _lives(0),
    _scoreValue(0), _spriteFilePath(""),
    _movePattern(), _transform(nullptr)
{
    init(mobtype);
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
    _movePattern(other._movePattern), _transform(other._transform)
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

/*
** Public member functions
*/
void        Mob::init(RType::MobType::IMobType const* type)
{
    _id = type->getId();
    _name = type->getName();
    _lives = type->getNbLives();
    _scoreValue = type->getScoreValue();
    _spriteFilePath = type->getSpriteFilePath();
    _movePattern = type->getMovePattern();
}

bool        Mob::handleMessage(Collider *o)
{
    GameObject	*otherParent = static_cast<GameObject *>(o->parent());

    if ((otherParent->getComponent<Player>() != nullptr
        || otherParent->getComponent<Behaviour>() != nullptr) && _lives != 0)
        _lives -= 1;
    return (true);
}

void		Mob::move(double elapsedTime)
{
    cu::Position    pos =
        _movePattern(_transform->getPosition(), elapsedTime);

    _transform->getPosition().setX(pos.X());
    _transform->getPosition().setY(pos.Y());
}

void		Mob::update(double elapsedTime)
{
    GameObject	*p = static_cast<GameObject *>(parent());

    if (_lives <= 0)
    {
        std::cout << "Mob Mort" << std::endl;
        _enabled = false;
        p->setVisible(false);
        p->getComponent<Collider>()->setEnabled(false);
    }
    if (!_transform)
        _transform = p->getComponent<Transform>();
    if (_transform->getPosition().X() > Renderer::width + 100
        || _transform->getPosition().X() < -100
        || _transform->getPosition().Y() > Renderer::height + 100
        || _transform->getPosition().Y() < -100)
        _enabled = false;
    this->move(elapsedTime);
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

RType::MobType::MovePattern const&      Mob::getMovePattern() const
{
    return _movePattern;
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
}

namespace std
{
    template<>
    void swap<Mob>(Mob& a, Mob& b)
    {
        a.swap(b);
    }
}
