#ifndef ICOMPONENT_HPP_
# define ICOMPONENT_HPP_

# include <string>
# include "ComponentMask.hpp"

namespace ECS
{
  class IComponent
  {
  public:
    virtual ~IComponent() {}

  public:
    virtual std::string     getName() const = 0;
    virtual ComponentMask   getMask() const = 0;
    virtual IComponent*     clone() const = 0;
    virtual void            clear() = 0;
  };
}

#endif /* !ICOMPONENT_HPP_ */
