//
// Created by Denis Le Borgne on 18/12/2015.
//

#include "IncompleteRequest.hpp"
#include "SocketMonitor.hpp"
#include "NetworkSystem.hpp"

namespace RType
{

    const short NetworkSystem::defaultPortTCP = 6667;
    const std::string NetworkSystem::defaultAddr = "127.0.0.1";
    const size_t      NetworkSystem::buffLen        = 1024;
    const short       NetworkSystem::defaultPortUDP = 6668;

    NetworkSystem::NetworkSystem(EntityManager *em, std::string const& addr, short int tcp, short int udpPort)
            : _entityManager(em), _monitor(SocketMonitor::getInstance()),
              _connector(addr, tcp), _udpSock(udpPort)
    {
        (void)_entityManager;
        _udpSock.setTimeoutSec(0);
        _udpSock.setTimeoutUsec(1000);
        _connector.connect();
        SocketMonitor::getInstance().registerSocket(&_connector);
    }

    NetworkSystem::~NetworkSystem()
    {
        _connector.close();
    }

    void NetworkSystem::processTCP()
    {
        Buffer receive;

        try
        {
            _monitor.update();
        }
        catch (std::runtime_error const&)
        { }

        if (_monitor.isReadable(&_connector))
        {
            try
            {
                _connector.receive(receive, buffLen);
            }
            catch (std::runtime_error const&)
            {
                _connector.close();
                _monitor.deleteSocket(&_connector);
                //TODO Send UI disconnection
            }
            _tcpObj.receive(receive);
        }
        if (_monitor.isWritable(&_connector))
            _connector.send(_tcpObj.toSend());
    }

    std::string NetworkSystem::toString() const
    {
        std::ostringstream ss;

        ss << "NetworkSystem {"
        << "\n\t Connector : " << this->_connector.toString()
        << "\n}" << std::endl;

        return ss.str();
    }

    void NetworkSystem::processUDP()
    {
        Buffer      receive;
        std::string addr;

        try
        {
            _udpSock.receiveFrom(receive, buffLen, addr);
        }
        catch (std::runtime_error const&)
        {
            _udpSock.close();
            //TODO Send UI disconnection
        }
        _udpObj.receive(receive);

        try
        {
            _udpSock.sendTo(_udpObj.toSend(), _addr);
        }
        catch (std::runtime_error const&)
        { }
    }

    void NetworkSystem::pushTCP(Request const& request)
    {
        _tcpObj.pushRequest(request);
    }

    void NetworkSystem::pushUDP(InGameEvent const& request)
    {
        _udpObj.pushRequest(request);
    }

    Request NetworkSystem::popTCP()
    {
        return (_tcpObj.popRequest());
    }

    InGameEvent NetworkSystem::popUDP()
    {
        return (_udpObj.popRequest());
    }
}
