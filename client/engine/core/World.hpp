//
// Created by fourdr_b on 08/12/15.
//

#ifndef RTYPE_WORLD_HPP
# define RTYPE_WORLD_HPP

# include <chrono>
#include <Renderer.hpp>
# include "EntityManager.hpp"
#include "CommandSystem.hpp"
#include "BehaviourSystem.hpp"

class World
{
public:
    World(EntityManager *em);

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

    double _lag;
};


#endif //RTYPE_WORLD_HPP
