//
// Created by naliwe on 23/12/15.
//

#include "CommandPipeline.hpp"

CommandPipeline::CommandPipeline()
        : _maxLag(1000)
{ }

void CommandPipeline::addCommand(ACommand *cmd)
{
    if (validate(cmd))
    {
        _commands.push_back(cmd);
        _commands.back()->execute();
    }
    else
    {
        _invalidCmd = cmd;
        replace(getDiff(cmd->getTime()), simulate(getDiff(cmd->getTime())));
    }
}

bool CommandPipeline::validate(ACommand *cmd)
{
    auto diff = std::chrono::high_resolution_clock::now() - cmd->getTime();

    std::cout << "Command lag = " << diff.count() << std::endl;

    return (diff <= _maxLag);
}

CommandPipeline::ms CommandPipeline::getMaxLag() const
{
    return (_maxLag);
}

void CommandPipeline::setMaxLag(CommandPipeline::ms newMaxLag)
{
    _maxLag = newMaxLag;
}

void CommandPipeline::replace(CommandPipeline::cmdIt const& pos, std::deque<ACommand *>& diff)
{
    int i = 0;

    for (cmdIt it = _commands.end(); it != pos; --it)
    {
        (*it)->undo();
        i++;
    }

    while (i-- > 0)
        _commands.pop_back();

    while (diff.size() > 0)
    {
        auto tmp = diff.front();

        _commands.push_back(tmp);
        _commands.back()->execute();

        diff.pop_front();
    }
}

std::deque<ACommand *>& CommandPipeline::simulate(CommandPipeline::cmdIt const& pos)
{
    _cmdDiff.clear();

    _cmdDiff.push_back(_invalidCmd);
    //TODO: [Opti] Check whether the cmd following the invalid one are the same type or not.

    for (cmdIt it = pos; it != _commands.end(); ++it)
        _cmdDiff.push_back(*it);
    return (_cmdDiff);
}

CommandPipeline::cmdIt const CommandPipeline::getDiff(CommandPipeline::timePoint t)
{
    auto it = _commands.end();

    for (; it != _commands.begin(); --it)
        if ((*it)->getTime() < t)
            break;

    return (it);
}
