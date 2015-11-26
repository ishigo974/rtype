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

        return (dynamic_cast<T *>(_entities[_ids].get()));
    }

private:
    std::unordered_map<unsigned int, std::unique_ptr<Object> > _entities;
    unsigned int                                               _ids;
};


#endif //RTYPE_ENTITYMANAGER_HPP
