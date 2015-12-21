//
// Created by fourdr_b on 08/12/15.
//

#include "World.hpp"

World::World(EntityManager *em, CommandSystem *cmd, Renderer *re, BehaviourSystem *bs)
        : _em(em), _cmdSystem(cmd), _renderer(re), _behaviourSystem(bs)
{
    BigBen::getElapsedtime();
    _lag = 0.0;
    _end = false;
}

std::vector<GameObject *> const *World::getEntities() const
{
    return (&_entities);
}

void World::addEntity(GameObject *entity)
{
    _entities.push_back(entity);
}

void World::gameLoop()
{
    while (!_end)
    {
        double lag = BigBen::getElapsedtime();

        _cmdSystem->addCommand();

        while (lag >= BigBen::getFixedElapsedtime())
        {
            _behaviourSystem->process();
            lag -= BigBen::getFixedElapsedtime();
        }

        _renderer->render();
    }
}
