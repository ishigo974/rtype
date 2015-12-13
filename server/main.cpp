#include <iostream>
#include "Server.hpp"

int   main(int ac, char **av)
{
    short int   port = RType::Server::defaultPort;

    try {
        if (ac > 1)
            port = std::stoi(std::string(av[1]));

        RType::Server   server(port);

        server.run();
    } catch (std::invalid_argument const& e) {
        std::cout << "Usage: " << std::string(av[0]) << " PORT" << std::endl;
    } catch (std::exception const& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unexpected internal error" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
