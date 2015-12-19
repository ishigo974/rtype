#include "ValueError.hpp"

namespace Exception
{
  ValueError::ValueError(std::string const& message) throw() :
    std::runtime_error("Value error: " + message)
  {
  }

  ValueError::~ValueError() throw()
  {
  }
}
