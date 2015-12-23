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
    template<>
    void swap<GameManager>(GameManager &a, GameManager &b)
    {
        a.swap(b);
    }
}
