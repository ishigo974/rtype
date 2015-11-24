#include <sstream>
#include "EntityManager.hpp"

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
    for (auto&& pair : _inactives)
    {
      if (pair.second->getComponentMask() == mask)
      {
        unsigned int    id;

        id = pair.first;
        _actives[id] = std::unique_ptr<Entity>(std::move(pair.second));
        _inactives.erase(id);
        _actives[id]->clear();
        return *_actives[id];
      }
    }
    _actives[_nextId] = std::make_unique<Entity>(_nextId);
    for (auto&& pair : _components)
    {
      if ((mask & pair.first) != 0)
        _actives[_nextId]->addComponent(pair.second->clone());
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
    _actives.erase(it);
    return true;
  }

  bool              EntityManager::destroy(Entity const& entity)
  {
    return destroy(entity.getId());
  }

  void              EntityManager::registerComponent(IComponent* component)
  {
    _components[component->getMask()] = std::unique_ptr<IComponent>(component);
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
