#include <cmath>
#include <float.h>
#include "CommandSystem.hpp"
#include "MoveCommand.hpp"
#include "ShootCommand.hpp"

CommandSystem::CommandSystem(EntityManager *entityManager)
{
  _entityManager = entityManager;
  _statuses[cu::Event::UP] = false;
  _statuses[cu::Event::DOWN] = false;
  _statuses[cu::Event::LEFT] = false;
  _statuses[cu::Event::RIGHT] = false;
  _statuses[cu::Event::SHOOT] = false;
}

CommandSystem::~CommandSystem()
{
}

void	CommandSystem::addCommand(cu::Event event)
{
  switch (event.type)
    {
    case cu::Event::KeyPressed:
      _statuses[event.key] = true;
      break;
    case cu::Event::KeyReleased:
      _statuses[event.key] = false;
      break;
    default:
      break;
    }
  if (_statuses[cu::Event::UP] && _statuses[cu::Event::RIGHT])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::UP_RIGHT));
  else if (_statuses[cu::Event::UP] && _statuses[cu::Event::LEFT])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::UP_LEFT));
  else if (_statuses[cu::Event::DOWN] && _statuses[cu::Event::RIGHT])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::DOWN_RIGHT));
  else if (_statuses[cu::Event::DOWN] && _statuses[cu::Event::LEFT])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::DOWN_LEFT));
  else if (_statuses[cu::Event::UP])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::UP));
  else if (_statuses[cu::Event::DOWN])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::DOWN));
  else if (_statuses[cu::Event::RIGHT])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::RIGHT));
  else if (_statuses[cu::Event::LEFT])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::LEFT));
  if (_statuses[cu::Event::SHOOT])
    _commands.push_back(new MoveCommand(_entityManager, ACommand::SHOOT));
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

void		CommandSystem::invalidateCommandAtTimestamp(timestamp time)
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
