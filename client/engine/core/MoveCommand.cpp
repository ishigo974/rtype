#include <ctime>
#include <chrono>
#include "InGameEvent.hpp"
#include "MoveCommand.hpp"
#include "NetworkUDP.hpp"
#include "Player.hpp"

MoveCommand::MoveCommand(EntityManager *entityManager,
                         ACommand::Action direction)
{
    _entityManager = entityManager;
    _direction     = direction;
    _time          = BigBen::getTimeNow();
    execute();
}

MoveCommand::~MoveCommand()
{
}

void    MoveCommand::execute()
{
    std::vector<Object *> objs    = _entityManager->getByMask(
                                          ComponentMask::PlayerMask);
    std::vector<Object *> network = _entityManager
            ->getByMask(ComponentMask::UDPMask);

    RType::InGameEvent event;

    for (auto obj : objs)
      {
	Player *player = static_cast<GameObject *>(obj)->getComponent<Player>();
	if (player)
	  player->setAction(_direction);
      }
    switch (_direction)
    {
        case UP:
            event.setCode(RType::InGameEvent::CL_PLAYERUP);
            break;
        case DOWN:
            event.setCode(RType::InGameEvent::CL_PLAYERDOWN);
            break;
        case LEFT:
            event.setCode(RType::InGameEvent::CL_PLAYERLEFT);
            break;
        case RIGHT:
            event.setCode(RType::InGameEvent::CL_PLAYERRIGHT);
            break;
        default:
            break;
    }
    event.push<uint32_t>("time",
                         std::chrono::time_point_cast<std::chrono::milliseconds>
                                 (BigBen::getTimeNow()).time_since_epoch().count());
    RType::NetworkUDP* tmp;
     if ((tmp = static_cast<GameObject *>(network[0])->getComponent<RType::NetworkUDP>()) != NULL)
        tmp->pushRequest(event);
}

void    MoveCommand::undo()
{

}
