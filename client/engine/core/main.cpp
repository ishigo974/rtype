#include "RTypeGame.hpp"
#include "PlayerObject.hpp"

int main(int ac, char **av)
{
    short int   port = RTypeGame::defaultPort;
    std::string addr = RTypeGame::defaultAddr;

    try {
        if (ac > 1)
            addr = std::string(av[1]);
        if (ac > 2)
            port = std::stoi(std::string(av[2]));

        RTypeGame   game(addr, port);

        game.run();
    } catch (std::exception const& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unexpected internal error" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
