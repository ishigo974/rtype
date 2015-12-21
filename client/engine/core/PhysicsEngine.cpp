//
// Created by fourdr_b on 21/12/15.
//

#include "PhysicsEngine.hpp"
#include "Collider.hpp"

PhysicsEngine::PhysicsEngine(EntityManager *em)
        : _em(em)
{ }

void PhysicsEngine::process(double fixedElapsed)
{
    auto tmp = _em->getByMask(ComponentMask::ColliderMask);

    for (auto e : tmp)
    {
        auto left = static_cast<GameObject *>(e);
        auto lCol = left->getComponent<Collider>();

        lCol->fixedUpdate(fixedElapsed);

        for (auto f : tmp)
        {
            auto right = static_cast<GameObject *>(f);
            auto rCol = right->getComponent<Collider>();

            if (left != right)
            {
                if (lCol->intersects(rCol))
                {
                    left->sendMessage(rCol);
                    right->sendMessage(lCol);
                }
            }
        }
    }
}
