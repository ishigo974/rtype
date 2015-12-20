//
// Created by fourdr_b on 08/12/15.
//

#include "World.hpp"

World::World(EntityManager *em)
        : _em(em)
{
    BigBen::getElapsedtime();
    _lag = 0.0;
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
    double lag = BigBen::getElapsedtime();

    _cmdSystem->addCommand();

    while (lag >= BigBen::getFixedElapsedtime())
    {
        _behaviourSystem->process();
        lag -= BigBen::getFixedElapsedtime();
    }

    _renderer->render();
}
