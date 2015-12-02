#include <string>
#include <iostream>
#include "Buffer.hpp"
#include "UdpSocket.hpp"
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"
#include "SocketMonitor.hpp"

/*
 * TODO Patch Select
 */

union lol {
    int a;
    char b[4];
};

int main()
{
    Buffer toto;


//    toto.append(" TAMERE", 7);
//    toto.append(" TONPERE", 9);
    toto.append<int>(42);
    lol a;
    a.b[0] = toto[3];
    a.b[1] = toto[2];
    a.b[2] = toto[1];
    a.b[3] = toto[0];
    std::cout << a.a << std::endl;
}
