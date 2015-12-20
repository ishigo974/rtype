#ifndef ENTITYMANAGER_HPP_
# define ENTITYMANAGER_HPP_

# include <memory>
# include <unordered_map>
# include <algorithm>
# include <functional>
# include "Entity.hpp"
# include "IComponent.hpp"
# include "ComponentMask.hpp"
# include "IStringable.hpp"

namespace ECS
{
    class EntityManager
    {
    public:
        typedef std::unique_ptr<EntityManager>          UniqueEmPtr;
        typedef std::unique_ptr<Entity>                 UniqueEntityPtr;
        typedef std::unique_ptr<IComponent>             UniqueCompPtr;
        typedef std::unordered_map<unsigned int,
                                    UniqueEntityPtr>    EntityMap;
        typedef std::unordered_map<IComponent const*,
                                   unsigned int,
                                   std::hash<IComponent const*> >        ComponentIdMap;

    protected:
        EntityManager();

    public:
        virtual ~EntityManager();

    private:
        EntityManager(EntityManager const& other) = delete;
        EntityManager&          operator=(EntityManager const& other) = delete;

    public:
        static EntityManager&   getInstance();

    public:
        Entity&                 create(ComponentMask mask = 0);
        bool                    destroy(unsigned int id);
        bool                    destroy(Entity const& entity);
        Entity&                 get(unsigned int id) const;
        EntityCollection        getByMask(ComponentMask mask) const;
        Entity&                 getByCmpnt(IComponent const* cmp) const;
        void                    updateAll();
        void                    clean();
        void                    addCmpntEntityLink(IComponent const* cmpnt,
                                                   Entity const& e);
        void                    removeCmpntEntityLink(IComponent const*);

    public:
        void        registerComponent(UniqueCompPtr component);
        bool        removeComponent(ComponentMask mask);

    public:
        virtual std::string         toString() const;

    protected:
        unsigned int                _nextId;
        EntityMap                   _actives;
        EntityMap                   _inactives;
        ComponentMap                _components;
        ComponentIdMap              _cmpntsEntities;

    protected:
        static UniqueEmPtr          instance;
    };
}

#endif /* !ENTITYMANAGER_HPP_ */
