#ifndef ICOMPONENT_HPP_
# define ICOMPONENT_HPP_

# include <string>
# include <memory>
# include <unordered_map>
# include "ComponentMask.hpp"
# include "IStringable.hpp"

namespace ECS
{
  class IComponent : public IStringable
  {
  public:
    virtual ~IComponent() {}

  public:
    virtual std::string     getName() const = 0;
    virtual ComponentMask   getMask() const = 0;
    virtual IComponent*     clone() const = 0;
    virtual void            clear() = 0;
  };

  typedef std::unordered_map<ComponentMask,
                             std::unique_ptr<IComponent> >    ComponentMap;
}

#endif /* !ICOMPONENT_HPP_ */
