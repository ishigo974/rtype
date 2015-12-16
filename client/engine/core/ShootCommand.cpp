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

    for (auto obj : objs)
        static_cast<GameObject *>(obj)->getComponent<Player>()->setAction(ACommand::SHOOT);
}

void    ShootCommand::undo()
{

}
