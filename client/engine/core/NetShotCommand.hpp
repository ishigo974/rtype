//
// Created by fourdr_b on 24/12/15.
//

#ifndef RTYPE_NETSHOTCOMMAND_HPP
# define RTYPE_NETSHOTCOMMAND_HPP

# include "ACommand.hpp"

class NetShotCommand : public ACommand
{
public:
    NetShotCommand();
    NetShotCommand(GameObject *target, bool type, std::chrono::microseconds time);
    NetShotCommand(NetShotCommand const& o);
    NetShotCommand(NetShotCommand&& o);
    NetShotCommand& operator=(NetShotCommand other);

    virtual ~NetShotCommand();

    void swap(NetShotCommand& o);

public:
    virtual void execute();
    virtual void undo();

private:
    GameObject *_target;
    bool       _fire;
};


#endif //RTYPE_NETSHOTCOMMAND_HPP
