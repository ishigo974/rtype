//
// Created by fourdr_b on 25/11/15.
//

#include "EntityManager.hpp"

std::unordered_map<unsigned int, std::unique_ptr<Object> > EntityManager::_entities;
std::map<unsigned int, unsigned int>                       EntityManager::_hierarchy;

std::vector<Object *> EntityManager::getByMask(unsigned int mask)
{
    std::vector<Object *> tmp;

    for (auto &e : _entities)
    {
        if (e.second->findMask(mask))
            tmp.push_back(e.second.get());
	// std::cout << e.second->getName() << std::endl;
	// std::cout << e.second->getMask() << std::endl;
    }
    return (tmp);
}

EntityManager::~EntityManager()
{
    _entities.clear();
}

EntityManager::EntityManager()
{
    _ids = 0;
    _compIds = 0;
}

Object *EntityManager::getParentOf(Component *component)
{
    auto selected = _hierarchy.find(component->getId());

    return ((selected == _hierarchy.end() ? nullptr : _entities[_hierarchy[component->getId()]].get()));
}
