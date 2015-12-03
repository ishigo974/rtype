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
    std::cout << toto.get<int>() << std::endl;
}
