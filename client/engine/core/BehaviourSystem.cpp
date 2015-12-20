//
// Created by fourdr_b on 20/12/15.
//

#include "BehaviourSystem.hpp"
#include "Behaviour.hpp"

BehaviourSystem::BehaviourSystem(EntityManager *em)
        : _em(em)
{ }

void BehaviourSystem::process()
{
    for (auto e : _em->getByMask(ComponentMask::BehaviourMask))
    {
        Behaviour *comp = static_cast<GameObject *>(e)->getComponent<Behaviour>();

        if (comp->isEnabled())
            comp->update();
    }
}
