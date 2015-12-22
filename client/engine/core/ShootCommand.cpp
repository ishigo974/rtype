#include <AudioEffect.hpp>
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
    std::vector<Object *>sound = _entityManager->getByMask(SoundMask);

    for (auto obj : objs)
        static_cast<GameObject *>(obj)->getComponent<Player>()
                                      ->setAction(ACommand::SHOOT);
    RType::InGameEvent    event;

    //TODO: Change 1 to timestamp
    event.push<uint32_t>("time", 1);
    for (auto play : sound)
    {
        if (static_cast<GameObject *>(play)->getComponent<AudioEffect>()
            ->getName() == "Shot")
        {
            static_cast<GameObject *>(play)->getComponent<AudioEffect>()
                                           ->setSoundToPlay("../res/laser1.wav");
        }
    }
}

void    ShootCommand::undo()
{

}
