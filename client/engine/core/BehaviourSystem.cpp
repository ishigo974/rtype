//
// Created by fourdr_b on 20/12/15.
//

#include "BehaviourSystem.hpp"
#include "Behaviour.hpp"
#include "Collider.hpp"
#include "Player.hpp"
#include "Mob.hpp"
#include "Bullet.hpp"

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
    tmp.clear();

    tmp = _em->getByMask(ComponentMask::MobMask);
    for (auto e : tmp)
    {
        Mob *comp = static_cast<GameObject *>(e)->getComponent<Mob>();

        if (comp->isEnabled())
            comp->update(elapsed);
    }
    tmp.clear();

    tmp = _em->getByMask(ComponentMask::PlayerMask);
    for (auto e : tmp)
    {
        Player *comp = static_cast<GameObject *>(e)->getComponent<Player>();

        if (comp->isEnabled())
            comp->update(elapsed);
    }
    tmp.clear();

    tmp = _em->getByMask(ComponentMask::BulletMask);
    for (auto e : tmp)
    {
        Bullet *comp = static_cast<GameObject *>(e)->getComponent<Bullet>();

        if (comp->isEnabled())
        comp->update(elapsed);
    }
    tmp.clear();

    tmp = _em->getByMask(ComponentMask::ColliderMask);
    for (auto e : tmp)
    {
        Collider *comp = static_cast<GameObject *>(e)->getComponent<Collider>();

        if (comp->isEnabled())
            comp->fixedUpdate(elapsed);
    }
}
