#include <string>
#include <iostream>
#include <UdpSocket.hpp>
#include "Buffer.hpp"

/*
 * TODO Patch Select
 */
int main()
{
    UdpSocket   server(6668);
    Buffer      msg;
    Buffer      rcv;
    std::string addr;

    server.bind();
    server.receiveFrom(rcv, 42, addr);
    std::cout << "RECEIVE FROM " << addr << " " << rcv.size() << " length" <<
            std::endl;
    msg.setData("CAMARCHEPAS", 12);
    server.sendTo(msg, addr);
}