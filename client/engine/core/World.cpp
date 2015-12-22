//
// Created by fourdr_b on 08/12/15.
//

#include "World.hpp"

World::World(EntityManager *em, CommandSystem *cmd, Renderer *re,
             BehaviourSystem *bs, Input *i, PhysicsEngine *pe,
             RType::NetworkSystem *r, RType::UDPSystem *f, AudioEffectPlayer
             *audio)
        : _em(em), _cmdSystem(cmd), _renderer(re), _behaviourSystem(bs),
          _input(i), _pe(pe), _tcpSystem(r), _udpSystem(f), _audioSystem(audio)
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
    cu::Event e;
    _audioSystem->init();
    while (!_end)
    {
        double lag = BigBen::getElapsedtime();

        _udpSystem->process();
        _tcpSystem->process();
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
        _audioSystem->process();
        _renderer->render();
    }
}
