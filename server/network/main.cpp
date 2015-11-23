#include <string>
#include <iostream>
#include "Buffer.hpp"
#include "UdpSocket.hpp"
#include "TcpAcceptor.hpp"
#include "TcpSocket.hpp"

int main()
{
    Buffer toto;

    std::cout << (int) toto.empty() << std::endl;
    toto.setData(std::string("LABITE"));
    std::cout << (int) toto.empty() << std::endl;
    std::cout << toto.data()->c_str() << std::endl;
    toto.consume(2);
    std::cout << toto.data()->c_str() << std::endl;
    std::cout << (int) toto.empty() << std::endl;
    toto.append(" TAMERE", 8);
    std::cout << toto.data()->c_str() << std::endl;
    toto.consume(42);
    std::cout << toto.data()->c_str() << std::endl;
    std::cout << (int) toto.empty() << std::endl;
    TcpAcceptor tcpsock(2121);
    TcpSocket   *tmp;

    tmp = (TcpSocket *) tcpsock.accept();
    if (tmp != nullptr)
    {
        std::cout << tmp->getAddr() << std::endl;
        toto.setData("TU SUCE DES BITES\n", 18);
        std::cout << toto.data()->c_str() << std::endl;
        tmp->send(&toto);
        delete tmp;
    }
}
