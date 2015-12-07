#include <iostream>
#include "Server.hpp"

int   main(int ac, char **av)
{
  int port = 6667;

  if (ac > 1)
    port = std::stoi(std::string(av[1]));

  try {
    RType::Server   server(port);

    server.run();
  } catch (std::exception const& e) {

    std::cerr << "Fatal error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
