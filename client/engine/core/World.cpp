//
// Created by fourdr_b on 08/12/15.
//

#include "World.hpp"

World::World(EntityManager *em, CommandSystem *cmd, Renderer *re, BehaviourSystem *bs, Input *i, cu::Event* event)
: _em(em), _cmdSystem(cmd), _renderer(re), _behaviourSystem(bs), _input(i), _event(event)
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

void World::gameLoop()
{
    while (!_end)
    {
        double lag = BigBen::getElapsedtime();

        while (_input->pollEvent(*_event))
        {
            if (_event->type == cu::Event::Closed || _event->key == cu::Event::ESCAPE)
            {
                std::cout << "Close button pressed" << std::endl;
                return;
            }
        }

        _cmdSystem->addCommand();

        while (lag >= _fixedStep)
        {
            _behaviourSystem->process(lag / _fixedStep);
            lag -= _fixedStep;
        }

        _renderer->render();
    }
}
