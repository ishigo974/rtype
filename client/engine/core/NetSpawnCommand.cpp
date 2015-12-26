//
// Created by fourdr_b on 24/12/15.
//

#include "NetSpawnCommand.hpp"
#include "UDPView.hpp"

NetSpawnCommand::NetSpawnCommand()
{ }

NetSpawnCommand::NetSpawnCommand(GameObject *target, std::chrono::microseconds time, unsigned int id, float x, float y)
        : _spawner(target), _targetId(id), _targetX(x), _targetY(y)
{
    _time = time;
}

NetSpawnCommand::NetSpawnCommand(NetSpawnCommand const& other)
{
    _spawner  = other._spawner;
    _targetId = other._targetId;
    _targetX  = other._targetX;
    _targetY  = other._targetY;
}

NetSpawnCommand::NetSpawnCommand(NetSpawnCommand&& other) : NetSpawnCommand(other)
{
    swap(other);
}

NetSpawnCommand& NetSpawnCommand::operator=(NetSpawnCommand other)
{
    swap(other);

    return (*this);
}

NetSpawnCommand::~NetSpawnCommand()
{ }

void NetSpawnCommand::swap(NetSpawnCommand& o)
{
    using std::swap;

    swap(_spawner, o._spawner);
    swap(_targetId, o._targetId);
    swap(_targetX, o._targetX);
    swap(_targetY, o._targetY);
}

void NetSpawnCommand::execute()
{
  _spawner->getComponent<UDPView>()->pushReceive
    (RType::InGameEvent(RType::InGameEvent::SE_MOBSPAWNED));
}

void NetSpawnCommand::undo()
{
    //TODO: Find some way to delete it~
}
