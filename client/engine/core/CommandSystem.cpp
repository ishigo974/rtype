#include <cmath>
#include <float.h>
#include <HRChrono.hpp>
#include "CommandSystem.hpp"
#include "MoveCommand_.hpp"
#include "ShootCommand.hpp"
#include "TCPView.hpp"
#include "UDPView.hpp"

CommandSystem::CommandSystem(EntityManager *entityManager, Input *i, RType::NetworkSystem *ns, Time::HRChrono chrono)
        : _factory(entityManager)
{
    _input         = i;
    _entityManager = entityManager;
    _ns            = ns;
    _chrono        = chrono;

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
                _commands.push_back(
                        new ShootCommand(_entityManager, std::chrono::microseconds(_chrono.getElapsedTime())));
            else
                _commands.push_back(new MoveCommand_(_entityManager, _actions[a.first],
                                                     std::chrono::microseconds(_chrono.getElapsedTime())));
        }
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
    << "\n\tqueue sizeRecv: " << _commands.size()
    << "\n}";
    return (ss.str());
}

void CommandSystem::processNetwork()
{
    size_t                          i;
    std::vector<RType::Request>     tcpIn;
    std::vector<RType::InGameEvent> udpIn;
    // GameManager                     *gm = static_cast<GameManager *>(_entityManager->getByTag("GameManager"));
    //    ACommand*                       command;

    _ns->processTCP();
    _ns->processUDP();

    while (_ns->tcpSize() > 0)
        tcpIn.push_back(_ns->popTCP());
    while (_ns->udpSize() > 0)
        udpIn.push_back(_ns->popUDP());

    auto tcpObjs = _entityManager->getByMask(ComponentMask::TCPMask);
    auto udpObjs = _entityManager->getByMask(ComponentMask::UDPMask);

    for (auto e : tcpObjs)
    {
        i = 0;
        auto tmpComp = static_cast<GameObject *>(e)->getComponent<TCPView>();

        while (i < tcpIn.size())
            tmpComp->pushReceive(tcpIn[i++]);
        while (tmpComp->sizeToSend() > 0)
        {
            _ns->pushTCP(tmpComp->popToSend());
        }
    }
    for (auto e : udpObjs)
    {
        i = 0;
        auto tmpComp = static_cast<GameObject *>(e)->getComponent<UDPView>();

        while (i < udpIn.size())
        {
            //            if ((command = _factory.createCommand(udpIn[i++])))
            //  _pipeline.addCommand(command);
            // if (gm[udpIn[i].get<uint16_t>("player_id")].getId() == e->getId())
            tmpComp->pushReceive(udpIn[i++]);
        }
        while (tmpComp->sizeToSend() > 0)
            _ns->pushUDP(tmpComp->popToSend());
    }
}
