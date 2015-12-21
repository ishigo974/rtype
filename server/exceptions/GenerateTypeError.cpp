#include "GenerateTypeError.hpp"

namespace Exception
{
  GenerateTypeError::GenerateTypeError(std::string const& message) throw() :
    std::runtime_error("Not implemented: " + message)
  {
  }

  GenerateTypeError::~GenerateTypeError() throw()
  {
  }
}
