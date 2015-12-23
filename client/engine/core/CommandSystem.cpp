#include <cmath>
#include <float.h>
#include "CommandSystem.hpp"
#include "MoveCommand.hpp"
#include "ShootCommand.hpp"
#include "TCPView.hpp"
#include "UDPView.hpp"

CommandSystem::CommandSystem(EntityManager *entityManager, Input *i, RType::NetworkSystem *ns)
{
    _input         = i;
    _entityManager = entityManager;
    _ns            = ns;

    _actions[cu::Event::UP]    = ACommand::UP;
    _actions[cu::Event::DOWN]  = ACommand::DOWN;
    _actions[cu::Event::LEFT]  = ACommand::LEFT;
    _actions[cu::Event::RIGHT] = ACommand::RIGHT;
    _actions[cu::Event::SHOOT] = ACommand::SHOOT;
}

CommandSystem::~CommandSystem()
{ }

void    CommandSystem::processInput()
{
    for (auto& a : _actions)
    {
        if (_input->isKeyPressed(a.first))
        {
            if (a.first == cu::Event::SHOOT)
                _commands.push_back(new ShootCommand(_entityManager));
            else
                _commands.push_back(new MoveCommand(_entityManager, _actions[a.first]));
        }
    }
}

ACommand *CommandSystem::getByTimestamp(timestamp time)
{
    //TODO: Nope... Need to undo in reverse order.
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

unsigned long    CommandSystem::getSize() const
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

void CommandSystem::processNetwork()
{
    size_t                          i;
    std::vector<RType::Request>     tcpIn;
    std::vector<RType::InGameEvent> udpIn;

    _ns->processTCP();
    _ns->processUDP();

    while (_ns->tcpSize() > 0)
        tcpIn.push_back(_ns->popTCP());

    while (_ns->udpSize() > 0)
        udpIn.push_back(_ns->popUDP());

    auto tcpObjs = _entityManager->getByMask(ComponentMask::TCPMask);
    auto udpObjs = _entityManager->getByMask(ComponentMask::UDPMask);

    i = 0;
    for (auto e : tcpObjs)
    {
        auto tmpComp = static_cast<GameObject *>(e)->getComponent<TCPView>();

        while (i < tcpIn.size())
            tmpComp->push(tcpIn[i++]);
        while (tmpComp->size() > 0)
            _ns->pushTCP(tmpComp->pop());
    }

    i = 0;
    for (auto e : udpObjs)
    {
        auto tmpComp = static_cast<GameObject *>(e)->getComponent<UDPView>();

        while (i < udpIn.size())
            tmpComp->push(udpIn[i++]);
        while (tmpComp->size() > 0)
            _ns->pushUDP(tmpComp->pop());
    }
}
