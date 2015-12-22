#include "NetworkUDP.hpp"
#include "ShootCommand.hpp"
#include "Player.hpp"

ShootCommand::ShootCommand(EntityManager *entityManager)
{
    _entityManager = entityManager;
    _time          = BigBen::getTimeNow();
    execute();
}

ShootCommand::~ShootCommand()
{

}

void    ShootCommand::execute()
{
    std::vector<Object *> objs    =
            _entityManager->getByMask(ComponentMask::PlayerMask);
    std::vector<Object *> network = _entityManager
            ->getByMask(ComponentMask::UDPMask);
    RType::InGameEvent  event;
    RType::NetworkUDP*  udp;

    for (auto obj : objs)
        static_cast<GameObject *>(obj)->getComponent<Player>()
                                      ->setAction(ACommand::SHOOT);

    event.setCode(RType::InGameEvent::CL_SHOTSTART);
    event.push<uint8_t>("shot_type", 0);
    event.push<uint32_t>("time",
                         std::chrono::time_point_cast<std::chrono::milliseconds>
                                 (BigBen::getTimeNow()).time_since_epoch().count());
    if (network.size() > 0)
    {
        if ((udp = static_cast<GameObject *>(network[0])
                ->getComponent<RType::NetworkUDP>()) != NULL)
            udp->pushRequest(event);
    }
}

void    ShootCommand::undo()
{

}
