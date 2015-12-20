//
// Created by fourdr_b on 08/12/15.
//

#include "World.hpp"

World::World(EntityManager *em)
        : _em(em)
{ }

std::vector<GameObject *> const * World::getEntities() const
{
    return (&_entities);
}

void World::addEntity(GameObject *entity)
{
    _entities.push_back(entity);
}

void World::gameLoop()
{
    
}
