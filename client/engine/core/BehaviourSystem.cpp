//
// Created by fourdr_b on 20/12/15.
//

#include "BehaviourSystem.hpp"
#include "Behaviour.hpp"

BehaviourSystem::BehaviourSystem(EntityManager *em)
        : _em(em)
{ }

void BehaviourSystem::process(double elapsed)
{
    auto tmp = _em->getByMask(ComponentMask::BehaviourMask);

    for (auto e : tmp)
    {
        Behaviour *comp = static_cast<GameObject *>(e)->getComponent<Behaviour>();

        if (comp->isEnabled())
            comp->update(elapsed);
    }
}
