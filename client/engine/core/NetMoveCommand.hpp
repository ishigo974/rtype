//
// Created by fourdr_b on 23/12/15.
//

#ifndef RTYPE_MOVECOMMAND_HPP
# define RTYPE_MOVECOMMAND_HPP

# include "InGameEvent.hpp"
# include "ACommand.hpp"

class NetMoveCommand : public ACommand
{
public:
    NetMoveCommand();
    NetMoveCommand(GameObject *target, ACommand::Action dir, std::chrono::microseconds time);
    NetMoveCommand(NetMoveCommand& o);
    NetMoveCommand(NetMoveCommand&& o);
    NetMoveCommand& operator=(NetMoveCommand o);

    virtual ~NetMoveCommand();

    void swap(NetMoveCommand& o);

public:
    virtual void execute();
    virtual void undo();

private:
    GameObject       *_target;
    ACommand::Action _direction;
    Transform        _origin;
};


#endif //RTYPE_MOVECOMMAND_HPP
