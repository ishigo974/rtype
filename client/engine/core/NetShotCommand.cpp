//
// Created by fourdr_b on 24/12/15.
//

#include "NetShotCommand.hpp"
#include "UDPView.hpp"

NetShotCommand::NetShotCommand()
{ }

NetShotCommand::NetShotCommand(GameObject *target, bool type)
        : _target(target), _fire(type)
{ }

NetShotCommand::NetShotCommand(NetShotCommand const& o)
{
    _target = o._target;
    _fire   = o._fire;
}

NetShotCommand::NetShotCommand(NetShotCommand&& o) : NetShotCommand(o)
{
    swap(o);
}

NetShotCommand& NetShotCommand::operator=(NetShotCommand other)
{
    swap(other);

    return (*this);
}

NetShotCommand::~NetShotCommand()
{ }

void NetShotCommand::swap(NetShotCommand& o)
{
    using std::swap;

    swap(_target, o._target);
    swap(_fire, o._fire);
}

void NetShotCommand::execute()
{
    _target->getComponent<UDPView>()->pushReceive((_fire)
                                                  ? UDPView::Action::SHOT_START
                                                  : UDPView::Action::SHOT_STOP);
}

void NetShotCommand::undo()
{
    _target->getComponent<UDPView>()->pushReceive((_fire)
                                                  ? UDPView::Action::SHOT_STOP
                                                  : UDPView::Action::SHOT_START);
}