//
// Created by fourdr_b on 23/12/15.
//

#include "GameManager.hpp"
#include "EntityManager.hpp"

GameManager::GameManager()
{ }

GameManager::GameManager(unsigned int id, std::string const& name, int layer)
 : GameObject(id, name, layer)
{ }

GameManager::GameManager(GameManager const& o) : GameObject(o)
{
    _targets = o._targets;
}

GameManager::GameManager(GameManager&& o)
{
    swap(o);
}

GameManager& GameManager::operator=(GameManager o)
{
    swap(o);

    return (*this);
}

GameObject *& GameManager::operator[](unsigned int id)
{
    return (_targets[id]);
}

void GameManager::swap(GameManager& o)
{
    using std::swap;

    swap(_targets, o._targets);
}

namespace std
{
    template <>
    void swap<GameManager>(GameManager &a, GameManager &b)
    {
        a.swap(b);
    }
}
void    GameManager::erasePlayer(unsigned int id)
{
    _targets.erase(id);
}

void    GameManager::clearPlayers()
{
    _targets.clear();
}

void    GameManager::setPlayerId(unsigned int id)
{
    _playerId = id;
}

GameManager::GameObjectMap::iterator    GameManager::begin()
{
    return _targets.begin();
}

GameManager::GameObjectMap::iterator    GameManager::end()
{
    return _targets.end();
}

GameManager::GameObjectMap::const_iterator    GameManager::begin() const
{
    return _targets.begin();
}

GameManager::GameObjectMap::const_iterator    GameManager::end() const
{
    return _targets.end();
}

unsigned int        GameManager::getPlayerId() const
{
    return _playerId;
}

std::string    GameManager::toString() const
{
    std::string res = std::string("GameManager {") +
                       "\n\t_playerId: " + std::to_string(_playerId) +
                       "\n\tplayers id: ";

    for (auto& target: _targets)
        res += std::to_string(target.first) + " ";
    return res + "\n}\n";
}
