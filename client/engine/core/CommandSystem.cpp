#include <cmath>
#include <float.h>
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
      _commands.push_back(new MoveCommand(MoveCommand::UP));
      break;
    case cu::Event::DOWN:
      _commands.push_back(new MoveCommand(MoveCommand::DOWN));
      break;
    case cu::Event::LEFT:
      _commands.push_back(new MoveCommand(MoveCommand::LEFT));
      break;
    case cu::Event::RIGHT:
      _commands.push_back(new MoveCommand(MoveCommand::RIGHT));
      break;
    case cu::Event::SHOOT:
      _commands.push_back(new ShootCommand());
      break;
    default:
      break;
    }
}

ACommand	*CommandSystem::getByTimestamp(timestamp time)
{
  std::chrono::duration<double>	diff;

  for (auto command : _commands)
    {
      diff = command->getTime() - time;
      if (abs(diff.count()) > DBL_EPSILON)
	return (command);
    }
  return NULL;
}

void		CommandSystem::process()
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
