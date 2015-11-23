#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <string>
# include <memory>
# include <unordered_map>
# include "IComponent.hpp"
# include "ComponentMask.hpp"
# include "IStringable.hpp"

namespace ECS
{
  class Entity : IStringable
  {
  protected:
    typedef std::unordered_map<ComponentMask,
                               std::unique_ptr<IComponent> >    ComponentMap;

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
          || (res = dynamic_cast<ComponentType*>(it->second)) == nullptr)
        return nullptr;
      return res;
    }

  public:
    unsigned int          getId() const;

  public:
    virtual std::string   toString() const;

  protected:
    unsigned int          _id;
    ComponentMask         _mask;
    ComponentMap          _components;
  };
}

#endif /* !ENTITY_HPP_ */
