#ifndef ENTITYMANAGER_HPP_
# define ENTITYMANAGER_HPP_

# include <memory>
# include <unordered_map>
# include "Entity.hpp"
# include "ComponentMask.hpp"
# include "IStringable.hpp"

namespace ECS
{
  class EntityManager
  {
  public:
    typedef std::unique_ptr<EntityManager>        UniqueEmPtr;
    typedef std::unique_ptr<Entity>               UniqueEntityPtr;
    typedef std::unordered_map<unsigned int,
                               UniqueEntityPtr>   EntityMap;

  protected:
    EntityManager();

  public:
    virtual ~EntityManager();

  private:
    EntityManager(EntityManager const& other) = delete;
    EntityManager&              operator=(EntityManager const& other) = delete;

  public:
    static EntityManager&       getInstance();

  public:
    Entity&                     create(ComponentMask mask = 0);
    void                        remove(unsigned int id);

  public:
    virtual std::string         toString() const;

  protected:
    EntityMap                   _actives;
    EntityMap                   _inactives;

  protected:
    static UniqueEmPtr          instance;
  };
}

#endif /* !ENTITYMANAGER_HPP_ */
