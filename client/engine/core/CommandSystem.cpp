#include <cmath>
#include <float.h>
#include "CommandSystem.hpp"
#include "MoveCommand.hpp"
#include "ShootCommand.hpp"

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
      _commands.push_back(new MoveCommand(_entityManager, ACommand::UP));
      break;
    case cu::Event::DOWN:
      _commands.push_back(new MoveCommand(_entityManager, ACommand::DOWN));
      break;
    case cu::Event::LEFT:
      _commands.push_back(new MoveCommand(_entityManager, ACommand::LEFT));
      break;
    case cu::Event::RIGHT:
      _commands.push_back(new MoveCommand(_entityManager, ACommand::RIGHT));
      break;
    case cu::Event::SHOOT:
      _commands.push_back(new ShootCommand(_entityManager));
      break;
    default:
      break;
    }
  // std::cout << _commands.size() << std::endl;
}

ACommand	*CommandSystem::getByTimestamp(timestamp time)
{
  std::chrono::duration<double>	diff;

  for (auto command : _commands)
    {
      diff = command->getTime() - time;
      if (abs(diff.count()) <= DBL_EPSILON)
	return (command);
    }
  return NULL;
}

void		CommandSystem::invalidCommandAtTimestamp(timestamp time)
{
  for (auto cmd : _commands)
    {
      if (cmd->getTime() > time)
	cmd->undo();
    }
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
