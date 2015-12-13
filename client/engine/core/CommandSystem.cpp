#include <cmath>
#include <float.h>
#include "CommandSystem.hpp"
#include "MoveCommand.hpp"
#include "ShootCommand.hpp"

CommandSystem::CommandSystem(EntityManager *entityManager, Input *i)
{
    _input         = i;
    _entityManager = entityManager;

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
    for (auto& a : _actions)
    {
        if (_input->isKeyPressed(a.first))
            _commands.push_back(new MoveCommand(_entityManager, _actions[a.first]));
    }
}

ACommand *CommandSystem::getByTimestamp(timestamp time)
{
    std::chrono::duration<double> diff;

    for (auto command : _commands)
    {
        diff = command->getTime() - time;
        if (fabs(diff.count()) <= DBL_EPSILON)
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
