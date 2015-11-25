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
    std::vector<Object *>   getByMask(unsigned int mask);
private:
    std::unordered_map<unsigned int, std::unique_ptr<Object> > _entities;
};


#endif //RTYPE_ENTITYMANAGER_HPP
