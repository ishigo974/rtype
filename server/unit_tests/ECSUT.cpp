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
    registerTest("EntityLifeRecycling", &ECSUT::entityLifeRecycling);
  }

  std::string   ECSUT::getName() const
  {
    return "ECS";
  }

  /*
  ** Unit tests
  */
  void          ECSUT::entityLifeRecycling()
  {
    EntityManager&    em      = EntityManager::getInstance();
    Entity&           entity  = em.create();

    UT_ASSERT(entity.getId() == 0);
    UT_ASSERT(entity.getComponentMask() == 0);
    entity = em.create();
    UT_ASSERT(entity.getId() == 1);
    UT_ASSERT(em.destroy(0) == true);
    entity = em.create();
    UT_ASSERT(entity.getId() == 0);
    entity = em.create();
    UT_ASSERT(entity.getId() == 2);
    entity = em.create();
    UT_ASSERT(entity.getId() == 3);
    UT_ASSERT(em.destroy(0) == true);
    UT_ASSERT(em.destroy(1) == true);
    UT_ASSERT(em.destroy(2) == true);
    UT_ASSERT(em.destroy(3) == true);
    entity = em.create();
    UT_ASSERT((entity.getId() == 0 || entity.getId() == 1
               || entity.getId() == 2 || entity.getId() == 3));
    UT_ASSERT(em.destroy(entity.getId()) == true);
  }
}
