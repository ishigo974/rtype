//
// Created by Denis Le Borgne on 18/12/2015.
//

#include "SocketMonitor.hpp"
#include "ClientNetwork.hpp"

namespace RType
{

    const short ClientNetwork::defaultPortUDP = 9999;
    const short ClientNetwork::defaultPortTCP = 6667;
    const std::string ClientNetwork::defaultAddr = "127.0.0.1";

    ClientNetwork::ClientNetwork(std::string const& addr, short tcp, short)
            : _monitor(SocketMonitor::getInstance()), _tcpManager(addr, tcp)
    { }

    ClientNetwork::~ClientNetwork()
    { }


    inline  void ClientNetwork::initTCPConnection()
    {
        _tcpManager.connect();
    }

    inline void ClientNetwork::initUDPConnection()
    {

    }
}
