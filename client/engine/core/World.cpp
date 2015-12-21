//
// Created by fourdr_b on 08/12/15.
//

#include "World.hpp"

World::World(EntityManager *em, CommandSystem *cmd, Renderer *re, BehaviourSystem *bs)
        : _em(em), _cmdSystem(cmd), _renderer(re), _behaviourSystem(bs)
{
    BigBen::getElapsedtime();
    _fixedStep = BigBen::getFixedElapsedtime();
    _lag       = 0.0;
    _end       = false;

    _renderer->init();
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

        while (lag >= _fixedStep)
        {
            _behaviourSystem->process(lag / _fixedStep);
            lag -= _fixedStep;
        }

        _renderer->render();
    }
}
