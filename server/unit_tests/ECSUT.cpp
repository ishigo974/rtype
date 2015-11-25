#include "ECSUT.hpp"
#include "EntityManager.hpp"

namespace ECS
{
  /*
  ** Constructor/Destructor
  */
  ECSUT::ECSUT()
  {
  }

  ECSUT::~ECSUT()
  {
  }

  /*
  ** Public member functions
  */
  void          ECSUT::registerTests()
  {
    registerTest("EntityLifeRecyclingSimple",
                 &ECSUT::entityLifeRecyclingSimple);
    registerTest("EntityLifeRecyclingWithComponent",
                 &ECSUT::entityLifeRecyclingWithComponent);
  }

  std::string   ECSUT::getName() const
  {
    return "ECS";
  }

  /*
  ** Unit tests
  */
  void          ECSUT::entityLifeRecyclingSimple()
  {
    EntityManager&    em      = EntityManager::getInstance();
    Entity*           entity  = &(em.create());

    UT_ASSERT(entity->getId() == 0);
    UT_ASSERT(entity->getComponentMask() == 0);
    entity = &(em.create());
    UT_ASSERT(entity->getId() == 1);
    UT_ASSERT(em.destroy(0) == true);
    entity = &(em.create());
    UT_ASSERT(entity->getId() == 0);
    entity = &(em.create());
    UT_ASSERT(entity->getId() == 2);
    entity = &(em.create());
    UT_ASSERT(entity->getId() == 3);
    UT_ASSERT(em.destroy(0) == true);
    UT_ASSERT(em.destroy(1) == true);
    UT_ASSERT(em.destroy(2) == true);
    UT_ASSERT(em.destroy(3) == true);
    entity = &(em.create());
    UT_ASSERT((entity->getId() == 0 || entity->getId() == 1
               || entity->getId() == 2 || entity->getId() == 3));
    UT_ASSERT(em.destroy(entity->getId()) == true);
    em.clean();
  }

  void          ECSUT::entityLifeRecyclingWithComponent()
  {
    EntityManager&    em      = EntityManager::getInstance();
    Entity*           entity;

    em.registerComponent(new Sample::Component1());
    em.registerComponent(new Sample::Component2());
    em.registerComponent(new Sample::Component3());

    entity = &(em.create(Sample::Component1::mask | Sample::Component2::mask));
    UT_ASSERT(entity->getId() == 0);
    UT_ASSERT(entity->getComponentMask() == (Sample::Component1::mask
                                             | Sample::Component2::mask));
    entity = &(em.create(Sample::Component3::mask));
    UT_ASSERT(entity->getId() == 1);
    UT_ASSERT(em.destroy(0) == true);
    UT_ASSERT(em.destroy(1) == true);
    entity = &(em.create(Sample::Component3::mask));
    UT_ASSERT(entity->getId() == 1);
    UT_ASSERT(em.destroy(1) == true);
    entity = &(em.create(Sample::Component1::mask
                         | Sample::Component2::mask));
    UT_ASSERT(entity->getId() == 0);
    entity = &(em.create(Sample::Component1::mask
                         | Sample::Component2::mask));
    UT_ASSERT(entity->getId() == 2);
    entity = &(em.create(Sample::Component1::mask
                         | Sample::Component2::mask));
    UT_ASSERT(entity->getId() == 3);
    UT_ASSERT(em.destroy(0) == true);
    UT_ASSERT(em.destroy(1) == false);
    UT_ASSERT(em.destroy(2) == true);
    UT_ASSERT(em.destroy(3) == true);
    em.clean();
  }

  namespace Sample
  {
    /* Component1 */
    const ComponentMask   Component1::mask = Sample::COMPMASK_ONE;

    Component1::Component1() {}
    Component1::~Component1() {}

    std::string     Component1::getName() const
    { return "Component1"; }

    ComponentMask   Component1::getMask() const
    { return mask; }

    IComponent*     Component1::clone() const
    { return new Component1(); }

    void            Component1::clear() {}

    /* Component2 */
    const ComponentMask   Component2::mask = Sample::COMPMASK_TWO;

    Component2::Component2() {}
    Component2::~Component2() {}

    std::string     Component2::getName() const
    { return "Component2"; }

    ComponentMask   Component2::getMask() const
    { return mask; }

    IComponent*     Component2::clone() const
    { return new Component2(); }

    void            Component2::clear() {}

    /* Component3 */
    const ComponentMask   Component3::mask = Sample::COMPMASK_THREE;

    Component3::Component3() {}
    Component3::~Component3() {}

    std::string     Component3::getName() const
    { return "Component3"; }

    ComponentMask   Component3::getMask() const
    { return mask; }

    IComponent*     Component3::clone() const
    { return new Component3(); }

    void            Component3::clear() {}
  }
}
