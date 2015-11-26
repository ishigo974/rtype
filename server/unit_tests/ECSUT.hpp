#ifndef ECSUT_HPP_
# define ECSUT_HPP_

# include <string>
# include "ABaseUT.hpp"
# include "ComponentMask.hpp"
# include "IComponent.hpp"
# include "ASystem.hpp"

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
    static void           entityLifeRecyclingWithComponent();
    static void           systemProcess();
    static void           systemManager();

  public:
    virtual void          registerTests();
    virtual std::string   getName() const;
  };

  namespace Sample
  {
    enum SampleMask : ComponentMask
    {
      COMPMASK_ONE    = 1 << 1,
      COMPMASK_TWO    = 1 << 2,
      COMPMASK_THREE  = 1 << 3
    };

    class Component1 : public IComponent
    {
    public:
      Component1();
      virtual ~Component1();

    public:
      std::string const&      getData() const;
      void                    setData(std::string const& data);

    public:
      virtual std::string     getName() const;
      virtual ComponentMask   getMask() const;
      virtual IComponent*     clone() const;
      virtual void            clear();

    public:
      static const ComponentMask    mask;

    protected:
      std::string             _data;
    };

    class Component2 : public IComponent
    {
    public:
      Component2();
      virtual ~Component2();

    public:
      std::string const&      getData() const;
      void                    setData(std::string const& data);

    public:
      virtual std::string     getName() const;
      virtual ComponentMask   getMask() const;
      virtual IComponent*     clone() const;
      virtual void            clear();

    public:
      static const ComponentMask    mask;

    protected:
      std::string             _data;
    };

    class Component3 : public IComponent
    {
    public:
      Component3();
      virtual ~Component3();

    public:
      virtual std::string     getName() const;
      virtual ComponentMask   getMask() const;
      virtual IComponent*     clone() const;
      virtual void            clear();

    public:
      static const ComponentMask    mask;
    };

    class System1 : public ASystem
    {
    public:
      System1();
      virtual ~System1();

    public:
      virtual void          processEntity(Entity& e);
      virtual ComponentMask getMask() const;
      virtual std::string   getName() const;
    };
  }
}

#endif /* !ECSUT_HPP_ */
