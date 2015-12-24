//
// Created by fourdr_b on 23/12/15.
//

#include "NetMoveCommand.hpp"
#include "UDPView.hpp"

NetMoveCommand::NetMoveCommand()
{ }


NetMoveCommand::NetMoveCommand(GameObject *target, ACommand::Action dir)
        : _target(target), _direction(dir)
{ }

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
    void swap<NetMoveCommand>(NetMoveCommand& a, NetMoveCommand& b)
    {
        a.swap(b);
    }
}

void NetMoveCommand::execute()
{
    _origin = Transform(_target->transform());

    switch (_direction)
    {
        case ACommand::Action::DOWN:
            _target->getComponent<UDPView>()->pushReceive(UDPView::Action::MOVE_DOWN);
            break;

        case ACommand::Action::UP:
            _target->getComponent<UDPView>()->pushReceive(UDPView::Action::MOVE_UP);
            break;

        case ACommand::Action::LEFT:
            _target->getComponent<UDPView>()->pushReceive(UDPView::Action::MOVE_LEFT);
            break;

        case ACommand::Action::RIGHT:
            _target->getComponent<UDPView>()->pushReceive(UDPView::Action::MOVE_RIGHT);
            break;

        default:
            break;
    }
}

void NetMoveCommand::undo()
{
    _target->transform() = Transform(_origin);
}
