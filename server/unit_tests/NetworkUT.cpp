//
// Created by Denis Le Borgne on 13/12/2015.
//

#include "NetworkUT.hpp"

NetworkUT::NetworkUT()
{}

NetworkUT::~NetworkUT()
{}

void            NetworkUT::registerTests()
{
    registerTest("Connect 1 client", &NetworkUT::simpleServerConnect);
    registerTest("Connect 4 client", &NetworkUT::multipleServerConnect);
    registerTest("Monitor 1 socket", &NetworkUT::simpleUpdate);
    registerTest("Monitor send", &NetworkUT::sendMonitor);
}

std::string     NetworkUT::getName() const
{
    return "Network";
}

void NetworkUT::multipleConnectMonitor()
{ }

void NetworkUT::sendMonitor()
{
    TcpAcceptor   acceptor(5555);
    TcpConnector  connector("127.0.0.1", 5555);
    SocketMonitor monitor;
    ISocket       *socket;
    Buffer        msg;
    Buffer        rcv;

    msg.setData("A simple message", 17);
    monitor.registerSocket(&acceptor);
    connector.connect();
    monitor.update();
    UT_ASSERT(monitor.isReadable(&acceptor) == true);
    socket = acceptor.accept();
    monitor.registerSocket(socket);
    monitor.update();
    UT_ASSERT(monitor.isWritable(socket) == true);
    socket->send(msg);
    connector.receive(rcv, msg.size());
    UT_ASSERT(rcv.size() == msg.size());
    UT_ASSERT(msg.getString() == rcv.getString());
}

void NetworkUT::simpleUpdate()
{
    TcpAcceptor   acceptor(7777);
    TcpConnector  connector("127.0.0.1", 7777);
    SocketMonitor monitor;

    monitor.registerSocket(&acceptor);
    connector.connect();
    monitor.update();
    UT_ASSERT(monitor.isReadable(&acceptor) == true);
}

void NetworkUT::multipleServerConnect()
{
    Buffer       msg;
    Buffer       rcv;
    TcpAcceptor  acceptor(6660);
    ISocket      *sock;
    ISocket      *sock1;
    ISocket      *sock2;
    ISocket      *sock3;
    TcpConnector client("127.0.0.1", 6660);
    TcpConnector client1("127.0.0.1", 6660);
    TcpConnector client2("127.0.0.1", 6660);
    TcpConnector client3("127.0.0.1", 6660);

    msg.setData("A simple message", 17);
    client.connect();
    sock = acceptor.accept();
    sock->send(msg);
    client.receive(rcv, msg.size());
    UT_ASSERT(rcv.size() == msg.size());
    UT_ASSERT(msg.getString() == rcv.getString());
    rcv.clear();
    client1.connect();
    sock1 = acceptor.accept();
    sock1->send(msg);
    client1.receive(rcv, msg.size());
    UT_ASSERT(rcv.size() == msg.size());
    UT_ASSERT(msg.getString() == rcv.getString());
    rcv.clear();
    client2.connect();
    sock2 = acceptor.accept();
    sock2->send(msg);
    client2.receive(rcv, msg.size());
    UT_ASSERT(rcv.size() == msg.size());
    UT_ASSERT(msg.getString() == rcv.getString());
    rcv.clear();
    client3.connect();
    sock3 = acceptor.accept();
    sock3->send(msg);
    client3.receive(rcv, msg.size());
    UT_ASSERT(rcv.size() == msg.size());
    UT_ASSERT(msg.getString() == rcv.getString());
    rcv.clear();
}

void NetworkUT::simpleServerConnect()
{
    Buffer       msg;
    Buffer       rcv;
    TcpAcceptor  acceptor(6661);
    ISocket      *sock;
    TcpConnector client1("127.0.0.1", 6661);

    msg.setData("A simple message", 17);
    client1.connect();
    sock = acceptor.accept();
    sock->send(msg);
    client1.receive(rcv, 17);
    UT_ASSERT(rcv.size() == msg.size());
    UT_ASSERT(msg.getString() == rcv.getString());
}
