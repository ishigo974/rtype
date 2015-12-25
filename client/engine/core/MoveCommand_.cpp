#include <ctime>
#include <chrono>
#include "InGameEvent.hpp"
#include "MoveCommand_.hpp"
#include "NetworkUDP.hpp"
#include "Player.hpp"

MoveCommand_::MoveCommand_(EntityManager *entityManager,
                           ACommand::Action direction)
{
    _entityManager = entityManager;
    _direction     = direction;
    _time          = BigBen::getTimeNow();
    execute();
}

MoveCommand_::~MoveCommand_()
{ }

void    MoveCommand_::execute()
{
    std::vector<Object *> objs = _entityManager->getByMask(ComponentMask::PlayerMask);
    RType::InGameEvent    event;

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

    //TODO: Change 1 to timestamp
    event.push<uint32_t>("time", 1);
}

void    MoveCommand_::undo()
{

}
