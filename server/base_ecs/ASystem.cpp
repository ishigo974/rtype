#include <algorithm>
#include <utility>
#include "ASystem.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

namespace ECS
{
  /*
  ** Constructor/Destructor
  */
  ASystem::ASystem()
  {
  }

  ASystem::~ASystem()
  {
  }

  /*
  ** Public member functions
  */
  void                  ASystem::process()
  {
    EntityCollection    entities =
      EntityManager::getInstance().getByMask(getMask());

    for (auto&& entity: entities)
      processEntity(*entity);
  }
}
