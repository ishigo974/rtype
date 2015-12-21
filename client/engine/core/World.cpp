//
// Created by fourdr_b on 08/12/15.
//

#include "World.hpp"

World::World(EntityManager *em, CommandSystem *cmd, Renderer *re, BehaviourSystem *bs, Input *i, PhysicsEngine *pe)
        : _em(em), _cmdSystem(cmd), _renderer(re), _behaviourSystem(bs), _input(i), _pe(pe)
{
    BigBen::getElapsedtime();
    _fixedStep = 0.003;
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

#include <unistd.h>

void World::gameLoop()
{
    cu::Event e;
    while (!_end)
    {
        double lag = BigBen::getElapsedtime();

        while (_input->pollEvent(e))
        {
            if (e.type == cu::Event::Closed || e.key == cu::Event::ESCAPE)
            {
                std::cout << "Close button pressed" << std::endl;
                return;
            }
        }

        _cmdSystem->process();

        while (lag >= _fixedStep)
        {
            _behaviourSystem->process(lag / _fixedStep);
            lag -= _fixedStep;
        }

        _pe->process(BigBen::getFixedElapsedtime());
        _renderer->render();
    }
}
