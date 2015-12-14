#include "MoveCommand.hpp"
#include "Player.hpp"

MoveCommand::MoveCommand(EntityManager *entityManager, ACommand::Action direction)
{
  _entityManager = entityManager;
  _direction = direction;
  _time = BigBen::getTimeNow();
  execute();
}

MoveCommand::~MoveCommand()
{
}

void	MoveCommand::execute()
{
  std::vector<Object *> objs = _entityManager->getByMask(ComponentMask::PlayerMask);

  for (auto obj : objs)
    static_cast<GameObject *>(obj)->getComponent<Player>()->setAction(_direction);
}

void	MoveCommand::undo()
{

}
