#include <cstdlib>
#include <iostream>
#include <string>
#include "UTManager.hpp"
#include "ECSUT.hpp"
#include "ProtocolUT.hpp"
#include "BaseFactoryUT.hpp"
#include "NetworkUT.hpp"

int           main(int ac, char **av)
{
    UnitTesting::UTManager   utm;

    if (ac < 3)
    {
        std::cout << av[0] << " IP PORT" << std::endl;
        return EXIT_SUCCESS;
    }
    utm.add(new ECS::ECSUT());
    utm.add(new RType::ProtocolUT(std::string(av[1]),
                                  std::stoi(std::string(av[2]))));
    utm.add(new Utils::BaseFactoryUT());
    utm.add(new NetworkUT());
    utm.run();
    return EXIT_SUCCESS;
}
