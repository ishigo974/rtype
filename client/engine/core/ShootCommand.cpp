#include "NetworkUDP.hpp"
#include "ShootCommand.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "UDPView.hpp"

ShootCommand::ShootCommand(EntityManager *entityManager, std::chrono::microseconds time)
{
    _entityManager = entityManager;
    _time          = time;
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
    GameManager* gm = static_cast<GameManager *>(_entityManager->getByTag("GameManager"));

    if (gm == nullptr)
        throw std::logic_error("Could not find GameManager");

    for (auto obj : objs)
        static_cast<GameObject *>(obj)->getComponent<Player>()
                                      ->setAction(ACommand::SHOOT);


    event.setCode(RType::InGameEvent::CL_SHOT);
    event.push<uint8_t>("shot_type", 0);
    event.push<uint64_t>("time", _time.count());
    UDPView* send = gm->getComponent<UDPView>();
    if (send != nullptr)
        if (send->sizeToSend())
            send->pushToSend(event);
}

void    ShootCommand::undo()
{

}
