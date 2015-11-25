#ifndef ECSUT_HPP_
# define ECSUT_HPP_

# include <string>
# include "ABaseUT.hpp"

namespace ECS
{
  class ECSUT : public UnitTesting::ABaseUT
  {
  public:
    ECSUT();
    virtual ~ECSUT();

  private:
    ECSUT(ECSUT const& other) = delete;
    ECSUT&                operator=(ECSUT const& other) = delete;

  protected:
    static void           entityLifeRecyclingSimple();

  public:
    virtual void          registerTests();
    virtual std::string   getName() const;
  };
}

#endif /* !ECSUT_HPP_ */
