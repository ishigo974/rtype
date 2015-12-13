#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
    {
      if (argc != 3)
	{
	  std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
	  return 1;
	}

      boost::asio::io_service io_service;

      tcp::resolver resolver(io_service);
      tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
      tcp::resolver::iterator iterator = resolver.resolve(query);

      tcp::socket socket(io_service);
      boost::asio::connect(socket, iterator);


      uint16_t code = 100;
      uint32_t size = 0;
      socket.send(boost::asio::buffer(&code, sizeof(code)));
      socket.send(boost::asio::buffer(&size, sizeof(size)));

      code = 301;
      size = sizeof(uint32_t) + 6;
      socket.send(boost::asio::buffer(&code, sizeof(code)));
      socket.send(boost::asio::buffer(&size, sizeof(size)));
      size = 6;
      socket.send(boost::asio::buffer(&size, sizeof(size)));
      std::cout << socket.send(boost::asio::buffer("teatea", 6)) << std::endl;

      code = 301;
      size = sizeof(uint32_t) + 6;
      socket.send(boost::asio::buffer(&code, sizeof(code)));
      socket.send(boost::asio::buffer(&size, sizeof(size)));
      size = 6;
      socket.send(boost::asio::buffer(&size, sizeof(size)));
      socket.send(boost::asio::buffer("tototo", 6));

      code = 100;
      size = 0;
      socket.send(boost::asio::buffer(&code, sizeof(code)));
      socket.send(boost::asio::buffer(&size, sizeof(size)));
      
      code = 101;
      size = sizeof(uint32_t) + 5;
      socket.send(boost::asio::buffer(&code, sizeof(code)));
      socket.send(boost::asio::buffer(&size, sizeof(size)));
      size = 5;
      socket.send(boost::asio::buffer(&size, sizeof(size)));
      socket.send(boost::asio::buffer("hello", 5));

      sleep(3);

      code = 103;
      size = 0;
      socket.send(boost::asio::buffer(&code, sizeof(code)));
      socket.send(boost::asio::buffer(&size, sizeof(size)));

      sleep(5);
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}

// int	main()
// {
//   TcpSocket	s("127.0.0.1", 6667);
//   Buffer	b;

//   b.append<uint16_t>(100);
//   b.append<uint32_t>(0);
//   s.send(b);
//   b.clear();
//   b.append<uint16_t>(101);
//   b.append<uint32_t>(sizeof(uint32_t) + 5);
//   b.append<std::string>("hello");
//   s.send(b);
//   return 0;
// }
