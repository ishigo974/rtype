//
// Created by fourdr_b on 24/12/15.
//

#ifndef RTYPE_NETSPAWNCOMMAND_HPP
# define RTYPE_NETSPAWNCOMMAND_HPP

# include "ACommand.hpp"

class NetSpawnCommand : public ACommand
{
public:
    NetSpawnCommand();
    NetSpawnCommand(GameObject *target, unsigned int id, float x, float y);
    NetSpawnCommand(NetSpawnCommand const& other);
    NetSpawnCommand(NetSpawnCommand&& other);
    NetSpawnCommand& operator=(NetSpawnCommand other);

    virtual ~NetSpawnCommand();

    void swap(NetSpawnCommand& o);

public:
    virtual void execute();
    virtual void undo();

private:
    GameObject   *_spawner;
    unsigned int _targetId;
    float        _targetX;
    float        _targetY;
};


#endif //RTYPE_NETSPAWNCOMMAND_HPP
