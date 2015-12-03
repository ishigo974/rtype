#include <cstdlib>
#include "UTManager.hpp"
#include "ECSUT.hpp"
#include "ProtocolUT.hpp"

int           main(int ac, char **av)
{
  UnitTesting::UTManager   utm;

  utm.add(new ECS::ECSUT());
  utm.add(new RType::ProtocolUT());
  utm.run(std::vector<std::string>(av + 1, av + ac));
  return EXIT_SUCCESS;
}
