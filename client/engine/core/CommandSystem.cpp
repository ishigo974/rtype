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
  _up = false;
  _down = false;
  _left = false;
  _right = false;
}

CommandSystem::~CommandSystem()
{
}

void	CommandSystem::addCommand(cu::Event event)
{
  // if (event.type == cu::Event::KeyPressed)
  //   {
  //     if (event.key == cu::Event::UP)
  // 	_up = true;
  //     else if (event.key == cu::Event::DOWN)
  // 	_down = true;
  //     else if (event.key == cu::Event::LEFT)
  // 	_left = true;
  //     else if (event.key == cu::Event::RIGHT)
  // 	_right = true;
  //   }
  // else if (event.type == cu::Event::KeyReleased)
  //   {
  //     if (event.key == cu::Event::UP)
  // 	_up = false;
  //     else if (event.key == cu::Event::DOWN)
  // 	_down = false;
  //     else if (event.key == cu::Event::LEFT)
  // 	_left = false;
  //     else if (event.key == cu::Event::RIGHT)
  // 	_right = false;
  //   }
  // // if (_up)
  // //   _commands.push_back(new MoveCommand(_entityManager, ACommand::UP));
  // // if (_down)
  // //   _commands.push_back(new MoveCommand(_entityManager, ACommand::DOWN));
  // // if (_left)
  // //   _commands.push_back(new MoveCommand(_entityManager, ACommand::LEFT));
  // // if (_right)
  // //   _commands.push_back(new MoveCommand(_entityManager, ACommand::RIGHT));

  // // switch (event.type)
  // //   {
  // //   case cu::Event::KeyPressed:
  // //     _statuses[event.key] = true;
  // //     break;
  // //   case cu::Event::KeyReleased:
  // //     _statuses[event.key] = false;
  // //     break;
  // //   default:
  // //     break;
  // //   }
  // // for (std::map<cu::Event::KeyEvent, bool>::iterator it = _statuses.begin(); it != _statuses.end(); ++it)
  // //   {
  // //     if (it->second)
  // // 	switch (it->first)
  // // 	  {
  // // 	  case cu::Event::UP:
  // // 	    _commands.push_back(new MoveCommand(_entityManager, ACommand::UP));
  // // 	    break;
  // // 	  case cu::Event::DOWN:
  // // 	    _commands.push_back(new MoveCommand(_entityManager, ACommand::DOWN));
  // // 	    break;
  // // 	  case cu::Event::LEFT:
  // // 	    _commands.push_back(new MoveCommand(_entityManager, ACommand::LEFT));
  // // 	    break;
  // // 	  case cu::Event::RIGHT:
  // // 	    _commands.push_back(new MoveCommand(_entityManager, ACommand::RIGHT));
  // // 	    break;
  // // 	  case cu::Event::SHOOT:
  // // 	    _commands.push_back(new ShootCommand(_entityManager));
  // // 	    break;
  // // 	  default:
  // // 	    break;
  // // 	  }
  // //   }




  switch (event.key)
    {
    case cu::Event::UP:
      _commands.push_back(new MoveCommand(_entityManager, ACommand::UP));
      _statuses[cu::Event::UP] = true;
      break;
    case cu::Event::DOWN:
      _commands.push_back(new MoveCommand(_entityManager, ACommand::DOWN));
      _statuses[cu::Event::DOWN] = true;
      break;
    case cu::Event::LEFT:
      _commands.push_back(new MoveCommand(_entityManager, ACommand::LEFT));
      _statuses[cu::Event::LEFT] = true;
      break;
    case cu::Event::RIGHT:
      _commands.push_back(new MoveCommand(_entityManager, ACommand::RIGHT));
      _statuses[cu::Event::DOWN] = true;
      break;
    case cu::Event::SHOOT:
      _commands.push_back(new ShootCommand(_entityManager));
      _statuses[cu::Event::SHOOT] = true;
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
