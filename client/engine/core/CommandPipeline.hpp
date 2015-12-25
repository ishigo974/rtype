//
// Created by naliwe on 23/12/15.
//

#ifndef RTYPE_COMMANDPIPELINE_HPP_
# define RTYPE_COMMANDPIPELINE_HPP_

# include <deque>
# include "ACommand.hpp"


class CommandPipeline
{
public:
    typedef std::deque<ACommand *>::const_iterator cmdIt;
    typedef std::chrono::microseconds              timePoint;

public:
    CommandPipeline();

public:
    void addCommand(ACommand *cmd);

public:
    timePoint getMaxLag() const;
    void      setMaxLag(timePoint newMaxLag);

private:
    bool        validate(ACommand *cmd);
    cmdIt const getDiff(timePoint t);
    void        replace(cmdIt const& pos, std::deque<ACommand *>& diff);

    std::deque<ACommand *>& simulate(cmdIt const& pos);

private:
    std::deque<ACommand *> _commands;
    std::deque<ACommand *> _cmdDiff;
    timePoint              _maxLag;
    ACommand               *_invalidCmd;
};


#endif /* !RTYPE_COMMANDPIPELINE_HPP_ */
