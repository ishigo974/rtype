#include "IncompleteRequest.hpp"

namespace Exception
{
  IncompleteRequest::IncompleteRequest(std::string const& message) throw() :
    std::runtime_error("Incomplete request: " + message)
  {
  }

  IncompleteRequest::~IncompleteRequest() throw()
  {
  }
}
