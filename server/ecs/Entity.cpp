#include <iostream>
#include <sstream>
#include "Entity.hpp"

namespace ECS
{
  /*
  ** Constructors/Destructor
  */
  Entity::Entity() : _id(0), _mask(0)
  {
  }

  Entity::Entity(unsigned int id) : _id(id), _mask(0)
  {
  }

  Entity::~Entity()
  {
  }

  /*
  ** Copy constructor and assign operator
  */
  Entity::Entity(Entity const& other) :
    _id(other._id), _mask(other._mask)
  {
    for (auto&& i : other._components)
      _components[i.first] = std::unique_ptr<IComponent>(i.second->clone());
  }

  Entity&         Entity::operator=(Entity const& other)
  {
    if (this != &other)
    {
      _id = other._id;
      _mask = other._mask;
      _components.clear();
      for (auto&& i : other._components)
        _components[i.first] = std::unique_ptr<IComponent>(i.second->clone());
    }
    return *this;
  }

  /*
  ** Public member functions
  */
  void            Entity::clear()
  {
    for (auto&& i : _components)
      i.second->clear();
  }

  void            Entity::addComponent(std::unique_ptr<IComponent> component)
  {
    _mask |= component->getMask();
    _components[component->getMask()] = std::move(component);
  }

  bool            Entity::removeComponent(ComponentMask mask)
  {
    if (_components.erase(mask) > 0)
    {
      _mask &= mask;
      return true;
    }
    return false;
  }

  unsigned int    Entity::getId() const
  {
    return _id;
  }

  ComponentMask   Entity::getComponentMask() const
  {
    return _mask;
  }

  std::string     Entity::toString() const
  {
    std::ostringstream  ss;

    ss << "Entity {"
       << "\n\t _id " << _id
       << "\n\t _mask " << _mask
       << "\n\t _components";
    for (auto&& i : _components)
      ss << " " << i.second->getName();
    ss << std::endl;
    return ss.str();
  }
}
