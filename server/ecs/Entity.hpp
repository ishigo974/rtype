#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <string>
# include <memory>
# include <vector>
# include "IComponent.hpp"
# include "ComponentMask.hpp"
# include "IStringable.hpp"

namespace ECS
{
  class Entity : IStringable
  {
  public:
    Entity();
    Entity(unsigned int id);
    virtual ~Entity();

  public:
    Entity(Entity const& other);
    Entity&               operator=(Entity const& other);

  public:
    void                  clear();

  public:
    void                  addComponent(IComponent* component);
    bool                  removeComponent(ComponentMask mask);

    template <typename ComponentType>
    ComponentType*        getComponent(ComponentMask mask) const
    {
      ComponentMap::const_iterator    it;
      ComponentType*                  res;

      if ((it = _components.find(mask)) == _components.end()
          || (res = dynamic_cast<ComponentType*>(it->second.get())) == nullptr)
        return nullptr;
      return res;
    }

  public:
    unsigned int          getId() const;
    ComponentMask         getComponentMask() const;

  public:
    virtual std::string   toString() const;

  protected:
    unsigned int          _id;
    ComponentMask         _mask;
    ComponentMap          _components;
  };

  typedef std::vector<Entity*>     EntityCollection;
}

#endif /* !ENTITY_HPP_ */
