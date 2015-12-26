//
// Created by fourdr_b on 23/12/15.
//

#include "NetMoveCommand.hpp"
#include "UDPView.hpp"

NetMoveCommand::NetMoveCommand()
{ }


NetMoveCommand::NetMoveCommand(GameObject *target, ACommand::Action dir, std::chrono::microseconds time)
        : _target(target), _direction(dir)
{
    _time = time;
}

NetMoveCommand::NetMoveCommand(NetMoveCommand& o)
{
    _target    = o._target;
    _direction = o._direction;
}

NetMoveCommand::NetMoveCommand(NetMoveCommand&& o) : NetMoveCommand(o)
{
    swap(o);
}

NetMoveCommand& NetMoveCommand::operator=(NetMoveCommand o)
{
    swap(o);

    return (*this);
}

NetMoveCommand::~NetMoveCommand()
{ }

void NetMoveCommand::swap(NetMoveCommand& o)
{
    using std::swap;

    swap(_target, o._target);
    swap(_direction, o._direction);
}

namespace std
{
    template<>
    inline void swap<NetMoveCommand>(NetMoveCommand& a, NetMoveCommand& b)
    {
        a.swap(b);
    }
}

void NetMoveCommand::execute()
{
    _origin = Transform(_target->transform());

    if (!_target && !_target->getComponent<UDPView>())
    {
      switch (_direction)
        {
            case ACommand::Action::DOWN:
                _target->getComponent<UDPView>()->pushReceive
                        (RType::InGameEvent(RType::InGameEvent::SE_PLAYERDOWN));
                break;
            case ACommand::Action::UP:
                _target->getComponent<UDPView>()->pushReceive
                        (RType::InGameEvent(RType::InGameEvent::SE_PLAYERUP));
                break;
            case ACommand::Action::LEFT:
                _target->getComponent<UDPView>()->pushReceive
                        (RType::InGameEvent(RType::InGameEvent::SE_PLAYERLEFT));
                break;
            case ACommand::Action::RIGHT:
                _target->getComponent<UDPView>()->pushReceive
                        (RType::InGameEvent(RType::InGameEvent::SE_PLAYERRIGHT));
                break;
            default:
                break;
        }
    }
}

void NetMoveCommand::undo()
{
    _target->transform() = Transform(_origin);
}
