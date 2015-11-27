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

int main()
{
    Buffer toto;

   // std::cout << (int) toto.empty() << std::endl;
    toto.setData(std::string("LABITE"));
   // std::cout << (int) toto.empty() << std::endl;
   // std::cout << toto.data()->c_str() << std::endl;
    toto.consume(2);
    //std::cout << toto.data()->c_str() << std::endl;
   // std::cout << (int) toto.empty() << std::endl;
    toto.append(" TAMERE", 8);
  //  std::cout << toto.data()->c_str() << std::endl;
    toto.consume(42);
 //   std::cout << toto.data()->c_str() << std::endl;
 //   std::cout << (int) toto.empty() << std::endl;
    TcpAcceptor tcpsock(2121);
    TcpSocket   *tmp;

    SocketMonitor test;

    test.registerSocket(&tcpsock);
    int retval;
    while ((retval = test.update()) >= 0 && errno != EINTR)
    {
        std::cout << "Retval : " << retval << std::endl;
        if (retval == 0)
            std::cerr << "Timeout" << std::endl;
        else if (retval > 0)
        {
            if (test.isReadable(&tcpsock))
            {
                tmp = static_cast<TcpSocket *>(tcpsock.accept());
                if (tmp != nullptr)
                {
                    std::cout << tmp->getAddr() << std::endl;
                    toto.setData("TU SUCE DES BITES\n", 18);
                    tmp->send(toto);
                    test.registerSocket(tmp);
                }
            }
        }
        std::cout << test.toString() << std::endl;
        test.clearFds();
        if (!test.isReadable(&tcpsock))
        {
            std::cout << "IsMonitored" << std::endl;
            test.registerSocket(&tcpsock);
        }
    }
}
