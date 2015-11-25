//
// Created by fourdr_b on 25/11/15.
//

#include "EntityManager.hpp"

std::vector<Object *> EntityManager::getByMask(unsigned int mask)
{
    std::vector<Object *> tmp;

    for (auto &&e : _entities)
    {
        if (e.second->getMask() == mask)
            tmp.push_back(e.second.get());
    }

    return (tmp);
}
