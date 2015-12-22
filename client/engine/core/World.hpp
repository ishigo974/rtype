//
// Created by fourdr_b on 08/12/15.
//

#ifndef RTYPE_WORLD_HPP
# define RTYPE_WORLD_HPP

# include <chrono>
# include <Renderer.hpp>
#include <NetworkSystem.hpp>
#include <UDPSystem.hpp>
# include "EntityManager.hpp"
# include "CommandSystem.hpp"
# include "BehaviourSystem.hpp"
# include "PhysicsEngine.hpp"
# include "AudioEffectPlayer.hpp"

class World
{
public:
    World(EntityManager *em, CommandSystem *cmd, Renderer *re,
          BehaviourSystem *bs, Input *i, PhysicsEngine *pe,
          RType::NetworkSystem *r, RType::UDPSystem *f, AudioEffectPlayer *);

public:
    std::vector<GameObject *> const *getEntities() const;
    void                            gameLoop();

public:
    template<class T, class ...Args>
    void addEntity(Args... args)
    {
        _entities.push_back(_em->createEntity<T>(args...));
    }

    void addEntity(GameObject *entity);

private:
    EntityManager             *_em;
    std::vector<GameObject *> _entities;
    CommandSystem             *_cmdSystem;
    Renderer                  *_renderer;
    BehaviourSystem           *_behaviourSystem;
    Input                     *_input;
    PhysicsEngine             *_pe;
    RType::NetworkSystem *_tcpSystem;
    RType::UDPSystem *_udpSystem;
    AudioEffectPlayer *_audioSystem;

    double _lag;
    double _fixedStep;
    bool   _end;
};


#endif //RTYPE_WORLD_HPP
