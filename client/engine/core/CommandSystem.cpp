#include "CommandSystem.hpp"
#include "MoveCommand.hpp"
#include "ShootCommand.hpp"
#include "InputHandler.hpp"

CommandSystem::CommandSystem(EntityManager *entityManager)
{
  _entityManager = entityManager;
}

CommandSystem::~CommandSystem()
{
}

void	CommandSystem::addCommand(cu::Event event)
{
  switch (event.key)
    {
    case cu::Event::UP:
      _commands.push(new MoveCommand(MoveCommand::UP));
      break;
    case cu::Event::DOWN:
      _commands.push(new MoveCommand(MoveCommand::DOWN));
      break;
    case cu::Event::LEFT:
      _commands.push(new MoveCommand(MoveCommand::LEFT));
      break;
    case cu::Event::RIGHT:
      _commands.push(new MoveCommand(MoveCommand::RIGHT));
      break;
    case cu::Event::SHOOT:
      _commands.push(new ShootCommand());
      break;
    default:
      break;
    }
}

void	CommandSystem::process()
{
  std::vector<Object *> objs = _entityManager->getByMask(ComponentMask::InputHandlerMask);

  for (auto obj : objs)
    static_cast<InputHandler *>(obj)->handleInput();
}

int	CommandSystem::getSize() const
{
  return _commands.size();
}

std::string	CommandSystem::toString()
{
  std::stringstream ss;

  ss << "CommandSystem {"
     << "\n\tqueue size: " << _commands.size()
     << "\n}";
  return (ss.str());
}
