#include "InvalidRequest.hpp"

namespace Exception
{
  InvalidRequest::InvalidRequest(std::string const& message) throw() :
    std::runtime_error("Invalid request: " + message)
  {
  }

  InvalidRequest::~InvalidRequest() throw()
  {
  }
}
