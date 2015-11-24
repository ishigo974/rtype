#include "AssertError.hpp"

namespace Exception
{
  AssertError::AssertError(std::string const& message) throw() :
    std::runtime_error(message)
  {
  }

  AssertError::~AssertError() throw()
  {
  }
}
