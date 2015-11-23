#include <string>
#include <iostream>
#include <cstdlib>
#include "Buffer.hpp"
#include "UdpSocket.hpp"

int main()
{
  Buffer toto;

  std::cout << (int)toto.empty() << std::endl;
  toto.setData(std::string("LABITE"));
  std::cout << (int)toto.empty() << std::endl;
  std::cout << toto.data()->c_str() << std::endl;
  toto.consume(2);
  std::cout << toto.data()->c_str() << std::endl;
  std::cout << (int)toto.empty() << std::endl;
    toto.append(" TAMERE", 8);
    std::cout << toto.data()->c_str() << std::endl;
  toto.consume(42);
  std::cout << toto.data()->c_str() << std::endl;
  std::cout << (int)toto.empty() << std::endl;
    IUdpSocket* lol = new UdpSocket(4242);
    lol->bind();
}
