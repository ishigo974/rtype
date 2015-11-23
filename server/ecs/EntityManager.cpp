#include "EntityManager.hpp"

namespace ECS
{
  /*
  ** Static variables
  */
  EntityManager::UniqueEmPtr      EntityManager::instance = nullptr;

  /*
  ** Constructor/Destructor
  */
  EntityManager::EntityManager()
  {
  }

  EntityManager::~EntityManager()
  {
  }

  /*
  ** Static functions
  */
  EntityManager&    EntityManager::getInstance()
  {
    if (EntityManager::instance == nullptr)
      EntityManager::instance =
        std::unique_ptr<EntityManager>(new EntityManager());
    return *EntityManager::instance;
  }

  /*
  ** Public member functions
  */
  Entity&           EntityManager::create(ComponentMask mask)
  {
    
  }

  void              EntityManager::remove(unsigned int id)
  {
  }

  std::string       EntityManager::toString() const
  {
  }
}
