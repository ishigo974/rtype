//
// Created by fourdr_b on 20/12/15.
//

#ifndef RTYPE_BEHAVIOURSYSTEM_HPP
# define RTYPE_BEHAVIOURSYSTEM_HPP

# include "EntityManager.hpp"

class BehaviourSystem
{
public:
    BehaviourSystem(EntityManager *em);

public:
    void process();

private:
    EntityManager *_em;
};


#endif //RTYPE_BEHAVIOURSYSTEM_HPP
