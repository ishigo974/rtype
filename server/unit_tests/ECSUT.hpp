#ifndef ECSUT_HPP_
# define ECSUT_HPP_

# include <string>
# include "ABaseUT.hpp"

namespace ECS
{
  class ECSUT : public ABaseUT
  {
  public:
    ECSUT();
    virtual ~ECSUT();

  private:
    ECSUT(ECSUT const& other) = delete;
    ECSUT&                operator=(ECSUT const& other) = delete;

  public:
    virtual void          registerTests();
    virtual std::string   getName();
  };
}

#endif /* !ECSUT_HPP_ */
