#include <sstream>
#include <iostream>
#include <algorithm>
#include "EntityManager.hpp"
#include "ValueError.hpp"

namespace ECS
{
    /*
    ** Static variables
    */
    EntityManager::UniqueEmPtr      EntityManager::instance = nullptr;

    /*
    ** Constructor/Destructor
    */
    EntityManager::EntityManager() : _nextId(0)
    {
    }

    EntityManager::~EntityManager()
    {
        _actives.clear();
        _inactives.clear();
        _components.clear();
        _cmpntsEntities.clear();
    }

    /*
    ** Static functions
    */
    EntityManager&    EntityManager::getInstance()
    {
        if (EntityManager::instance == nullptr)
            EntityManager::instance =
                std::unique_ptr<EntityManager>(new EntityManager());
        return *EntityManager::instance;
    }

    /*
    ** Public member functions
    */
    Entity&           EntityManager::create(ComponentMask mask)
    {
        EntityMap::iterator   it =
            std::find_if(_inactives.begin(), _inactives.end(),
            [mask](std::pair<const unsigned int,
                             UniqueEntityPtr> const& e)->bool
            { return e.second->getComponentMask() == mask; });

        if (it != _inactives.end())
        {
            unsigned int    id;

            id = it->first;
            _actives[id] = std::move(it->second);
            _inactives.erase(id);
            _actives[id]->clear();
            return *_actives[id];
        }
        _actives[_nextId] = std::make_unique<Entity>(_nextId);
        for (auto&& pair : _components)
        {
            if ((mask & pair.first) != 0)
                _actives[_nextId]
                    ->addComponent(UniqueCompPtr(pair.second->clone()));
        }
        ++_nextId;
        return *_actives[_nextId - 1];
    }

    bool              EntityManager::destroy(unsigned int id)
    {
        EntityMap::iterator it = _actives.find(id);

        if (it == _actives.end())
            return false;
        _inactives[id] = std::unique_ptr<Entity>(std::move(it->second));
        it->second = nullptr;
        _actives.erase(it);
        return true;
    }

    bool              EntityManager::destroy(Entity const& entity)
    {
        return destroy(entity.getId());
    }

    void              EntityManager::safeDestroy(Entity const& entity)
    {
        _toDestroy.insert(entity.getId());
    }

    Entity&           EntityManager::get(unsigned int id) const
    {
        EntityMap::const_iterator   it;

        if ((it = _actives.find(id)) == _actives.end())
            throw Exception::ValueError("Id " + std::to_string(id) +
                                        " does not match any entity");
        return *it->second;
    }

    void             EntityManager::addCmpntEntityLink(IComponent const* cmp,
                                                       Entity const& e)
    {
        _cmpntsEntities.insert(std::make_pair(cmp, e.getId()));
    }

    void             EntityManager::removeCmpntEntityLink(IComponent const* cmp)
    {
        _cmpntsEntities.erase(cmp);
    }

    Entity&           EntityManager::getByCmpnt(IComponent const* cmp) const
    {
        return get(_cmpntsEntities.at(cmp));
    }

    EntityCollection  EntityManager::getByMask(ComponentMask mask) const
    {
        EntityCollection  res;

        for (auto& entity : _actives)
            if ((entity.second->getComponentMask() & mask) == mask)
                res.push_back(entity.second.get());
        return res;
    }

    void                EntityManager::updateAll()
    {
        for (auto& id: _toDestroy)
            destroy(id);
        _toDestroy.clear();
        for (auto& entity: _actives)
            entity.second->update();
    }

    void              EntityManager::clean()
    {
        _actives.clear();
        _inactives.clear();
        _cmpntsEntities.clear();
        _nextId = 0;
    }

    void              EntityManager::registerComponent(UniqueCompPtr component)
    {
        _components[component->getMask()] = std::move(component);
    }

    bool              EntityManager::removeComponent(ComponentMask mask)
    {
        return _components.erase(mask) > 0;
    }

    std::string       EntityManager::toString() const
    {
        std::ostringstream  ss;

        ss << "EntityManager {"
        << "\n\t_nextId " << _nextId
        << "\n\t_actives(" << _actives.size() << ")";
        for (auto&& e : _actives)
        ss << " " << e.first;
        ss << "\n\t_inactives(" << _inactives.size() << ")";
        for (auto&& e : _inactives)
        ss << " " << e.first;
        ss << "\n\t_components";
        for (auto&& c : _components)
        ss << " " << c.second->getName();
        ss << std::endl;
        return ss.str();
    }
}
