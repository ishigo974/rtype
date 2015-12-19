//
// Created by fourdr_b on 25/11/15.
//

#include "EntityManager.hpp"

std::unordered_map<unsigned int, std::unique_ptr<Object> > EntityManager::
                                                                    _entities;
std::map<unsigned int, unsigned int>                       EntityManager::
                                                                   _compHierarchy;
std::map<unsigned int, unsigned int>                       EntityManager::
                                                                   _goHierarchy;
std::map<std::string, Object *>                            EntityManager::_tags;

std::vector<Object *> EntityManager::getByMask(unsigned int mask)
{
    std::vector<Object *> tmp;

    for (auto& e : _entities)
    {
        if (e.second->findMask(mask))
            tmp.push_back(e.second.get());
    }
    return (tmp);
}

EntityManager::~EntityManager()
{
    _entities.clear();
}

EntityManager::EntityManager()
{
    _ids     = 0;
    _compIds = 0;
}

Object *EntityManager::getParentOf(Component *component)
{
    auto selected = _compHierarchy.find(component->getId());

    return ((selected == _compHierarchy.end())
            ? nullptr
            : _entities[_compHierarchy[component->getId()]].get());
}

void EntityManager::addChild(GameObject *parent, GameObject *child)
{
    _goHierarchy[child->getId()] = parent->getId();
}

Object *EntityManager::getParentOf(GameObject *go)
{
    auto selected = _goHierarchy.find(go->getId());

    return ((selected == _goHierarchy.end())
            ? nullptr
            : _entities[_compHierarchy[go->getId()]].get());
}

std::vector<Object *> EntityManager::getChildrenOf(GameObject *go)
{
    std::vector<Object *> tmp;

    for (auto& e : _goHierarchy)
    {
        if (e.second == go->getId())
            tmp.push_back(_entities[e.first].get());
    }

    return (tmp);
}

void EntityManager::tagObject(Object *o, std::string const& tag)
{
    auto selected = _tags.find(tag);

    if (selected == _tags.end())
        _tags[tag] = o;
    else
        throw std::logic_error(std::string("Tag already exists : ")
                                       .append(tag).append(" for item ")
                                       .append(o->toString()));
}

Object *EntityManager::getByTag(std::string const& tag)
{
    auto selected = _tags.find(tag);

    if (selected != _tags.end())
        return (_tags[tag]);
    else
        throw std::logic_error(
                std::string("Could not find object with tag ").append(tag));
}
