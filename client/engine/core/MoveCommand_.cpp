#include <ctime>
#include <chrono>
#include "InGameEvent.hpp"
#include "MoveCommand_.hpp"
#include "NetworkUDP.hpp"
#include "Player.hpp"
#include "UDPView.hpp"
#include "GameManager.hpp"

MoveCommand_::MoveCommand_(EntityManager *entityManager,
                           ACommand::Action direction,
                           std::chrono::microseconds time)
{
    _entityManager = entityManager;
    _direction     = direction;
    _time          = time;
    execute();
}

MoveCommand_::~MoveCommand_()
{ }

void    MoveCommand_::execute()
{
    std::vector<Object *> objs = _entityManager->getByMask(ComponentMask::PlayerMask);
    RType::InGameEvent    event;
    GameManager* gm = static_cast<GameManager *>(_entityManager->getByTag("GameManager"));

    if (gm == nullptr)
      throw std::logic_error("Could not find GameManager");
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

    std::cout << "I MOVE " << event.getCode() << std::endl;
    event.push<uint64_t>("time", _time.count());
    UDPView* send = gm->getComponent<UDPView>();
    if (send != nullptr)
      send->pushToSend(event);
}

void    MoveCommand_::undo()
{

}
