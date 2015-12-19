#include "NotImplemented.hpp"

namespace Exception
{
  NotImplemented::NotImplemented(std::string const& message) throw() :
    std::runtime_error("Not implemented: " + message)
  {
  }

  NotImplemented::~NotImplemented() throw()
  {
  }
}
