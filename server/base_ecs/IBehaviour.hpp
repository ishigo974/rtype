#ifndef IBEHAVIOUR_HPP_
# define IBEHAVIOUR_HPP_

# include "IComponent.hpp"

namespace ECS
{
  class IBehaviour : public ECS::IComponent
  {
  public:
    virtual ~IBehaviour() {}

  public:
    virtual void    update() = 0;
  };
}

#endif /* !IBEHAVIOUR_HPP_ */
