//
// Created by fourdr_b on 20/12/15.
//

#include "BehaviourSystem.hpp"
#include "Behaviour.hpp"
#include "Collider.hpp"
#include "Player.hpp"
#include "Mob.hpp"
#include "Bullet.hpp"
#include "MobSpawner.hpp"

BehaviourSystem::BehaviourSystem(EntityManager *em)
        : _em(em)
{ }

void BehaviourSystem::process(double elapsed)
{
    static const std::vector<ComponentMask>     masks =
    {
        ComponentMask::BehaviourMask,   ComponentMask::MobMask,
        ComponentMask::PlayerMask,      ComponentMask::BulletMask,
        ComponentMask::MobSpawnerMask
    };

    for (auto& mask: masks)
    {
        auto tmp = _em->getByMask(mask);

        for (auto e : tmp)
        {
            Behaviour *comp = static_cast<GameObject *>(e)->getComponent<Behaviour>(mask);

            if (comp->isEnabled())
                comp->update(elapsed);
        }
    }

    auto tmp = _em->getByMask(ComponentMask::ColliderMask);
    for (auto e : tmp)
    {
        Collider *comp = static_cast<GameObject *>(e)->getComponent<Collider>();

        if (comp->isEnabled())
            comp->fixedUpdate(elapsed);
    }
}
