#include <cmath>
#include <float.h>
#include "CommandSystem.hpp"
#include "MoveCommand.hpp"
#include "ShootCommand.hpp"

CommandSystem::CommandSystem(EntityManager *entityManager, Input *i)
{
    _input = i;
    _entityManager = entityManager;
    _statuses[cu::Event::UP]    = false;
    _statuses[cu::Event::DOWN]  = false;
    _statuses[cu::Event::LEFT]  = false;
    _statuses[cu::Event::RIGHT] = false;
    _statuses[cu::Event::SHOOT] = false;

    _actions[cu::Event::UP]    = ACommand::UP;
    _actions[cu::Event::DOWN]  = ACommand::DOWN;
    _actions[cu::Event::LEFT]  = ACommand::LEFT;
    _actions[cu::Event::RIGHT] = ACommand::RIGHT;
    _actions[cu::Event::SHOOT] = ACommand::SHOOT;
}

CommandSystem::~CommandSystem()
{
}

void    CommandSystem::addCommand()
{
    for (auto it = _statuses.begin(); it != _statuses.end(); ++it)
    {
      if (_input->isKeyPressed(it->first))
  	_commands.push_back(new MoveCommand(_entityManager, _actions[it->first]));
    }
}

ACommand *CommandSystem::getByTimestamp(timestamp time)
{
    std::chrono::duration<double> diff;

    for (auto command : _commands)
    {
        diff = command->getTime() - time;
        if (abs(diff.count()) <= DBL_EPSILON)
            return (command);
    }
    return NULL;
}

void        CommandSystem::invalidateCommandAtTimestamp(timestamp time)
{
    for (auto cmd : _commands)
    {
        if (cmd->getTime() > time)
            cmd->undo();
    }
}

int    CommandSystem::getSize() const
{
    return _commands.size();
}

std::string    CommandSystem::toString()
{
    std::stringstream ss;

    ss << "CommandSystem {"
    << "\n\tqueue size: " << _commands.size()
    << "\n}";
    return (ss.str());
}
