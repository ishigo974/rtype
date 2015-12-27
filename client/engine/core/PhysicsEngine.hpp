//
// Created by fourdr_b on 21/12/15.
//

#ifndef RTYPE_PHYSICSENGINE_HPP
# define RTYPE_PHYSICSENGINE_HPP

# include "EntityManager.hpp"

class PhysicsEngine
{
public:
    PhysicsEngine(EntityManager *em);

public:
    void process(double fixedElapsed) const;

private:
    EntityManager *_em;
};


#endif //RTYPE_PHYSICSENGINE_HPP
