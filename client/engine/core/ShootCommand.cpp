#include "NetworkUDP.hpp"
#include "InGameEvent.hpp"
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
    std::vector<Object *> objs = _entityManager->getByMask(ComponentMask::PlayerMask);
    RType::InGameEvent event;
    std::vector<Object *> network = _entityManager
            ->getByMask(ComponentMask::UDPMask);

    for (auto obj : objs)
        static_cast<GameObject *>(obj)->getComponent<Player>()->setAction(ACommand::SHOOT);

//    event.setCode(RType::InGameEvent::CL_SHOTSTART);
//    event.push<uint32_t>("time",
//                         std::chrono::time_point_cast<std::chrono::milliseconds>
//                                 (BigBen::getTimeNow()).time_since_epoch()
//                                                       .count());
//    static_cast<GameObject *>(network[0])
//            ->getComponent<RType::NetworkUDP>()->pushRequest(event);
}

void    ShootCommand::undo()
{

}
