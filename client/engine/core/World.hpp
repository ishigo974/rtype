//
// Created by fourdr_b on 08/12/15.
//

#ifndef RTYPE_WORLD_HPP
# define RTYPE_WORLD_HPP

# include "EntityManager.hpp"

class World
{
public:
    World(EntityManager *em);

public:
    void update();

public:
    template<class T, class ...Args>
    void addEntity(Args... args)
    {
        _entities.push_back(_em->createEntity<T>(args...));
    }

private:
    EntityManager             *_em;
    std::vector<GameObject *> _entities;
};


#endif //RTYPE_WORLD_HPP
