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

    NetworkSystem::NetworkSystem(EntityManager *em, std::string const& addr,
                                 short int tcp, short int udpPort)
            : _entityManager(em), _monitor(SocketMonitor::getInstance()),
              _connector(addr, tcp), _udpSock(udpPort), _addr(addr)
    {
        _udpSock.setTimeoutSec(0);
        _udpSock.setTimeoutUsec(1000);
        _udpSock.bind();
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
        if (_monitor.isWritable(&_connector))
        {
            Buffer tmp = _tcpObj.toSend();
            if (!tmp.empty())
            {
                _connector.send(tmp);
            }
        }
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
            if ((_udpSock.receiveFrom(receive, buffLen, addr)) > 0)
                _udpObj.receive(receive);
        }
        catch (std::runtime_error const&)
        {
            _udpSock.close();
            std::cout << "denis est un fdp" << std::endl;
            //TODO Send UI disconnection
        }

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

    size_t NetworkSystem::tcpSize() const
    {
        return (_tcpObj.inSize());
    }

    size_t NetworkSystem::udpSize() const
    {
        return (_udpObj.inSize());
    }
}
