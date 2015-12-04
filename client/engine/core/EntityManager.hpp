//
// Created by fourdr_b on 25/11/15.
//

#ifndef RTYPE_ENTITYMANAGER_HPP
# define RTYPE_ENTITYMANAGER_HPP

# include <unordered_map>

# include <vector>
# include <algorithm>
# include <memory>
# include "Object.hpp"
#include "GameObject.hpp"

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    std::vector<Object *> getByMask(unsigned int mask);

    template<class T, class ...Args, typename = std::enable_if<std::is_base_of<Object, T>::value> >
    T *createEntity(Args ...args)
    {
        _ids += 1;
        _entities[_ids] = std::make_unique<T>(std::ref(_ids), args...);
        attachComponent<Transform>(static_cast<T *>(_entities[_ids].get()));

        return (static_cast<T *>(_entities[_ids].get()));
    }

    template<class T, class ...Args, typename = std::enable_if<std::is_base_of<Component, T>::value> >
    void attachComponent(GameObject *gameObject, Args ...args)
    {
        auto tmp = _entities.find(gameObject->getId());

        if (tmp != _entities.end())
        {
            _compIds += 1;
            _components[_compIds] = std::make_unique<T>(std::ref(_compIds), args...);

            static_cast<GameObject *>(tmp->second.get())->addComponent(static_cast<T *>(_components[_compIds].get()));
        }
    }

private:
    std::unordered_map<unsigned int, std::unique_ptr<Object> >    _entities;
    std::unordered_map<unsigned int, std::unique_ptr<Component> > _components;
    unsigned int                                                  _ids;
    unsigned int                                                  _compIds;
};


#endif //RTYPE_ENTITYMANAGER_HPP
