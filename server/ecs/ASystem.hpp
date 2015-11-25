#ifndef ASYSTEM_HPP_
# define ASYSTEM_HPP_

# include <vector>
# include "Entity.hpp"
# include "ComponentMask.hpp"

namespace ECS
{
  class ASystem
  {
  public:
    ASystem();
    virtual ~ASystem();

  private:
    ASystem(ASystem const& other) = delete;
    ASystem&              operator=(ASystem const& other) = delete;

  public:
    void                  process();

  public:
    virtual void          processEntity(Entity& e) = 0;
    virtual ComponentMask getMask() const = 0;
    virtual std::string   getName() const = 0;
  };
}

#endif /* !ASYSTEM_HPP_ */
