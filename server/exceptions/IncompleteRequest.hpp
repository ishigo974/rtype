#ifndef INCOMPLETEREQUEST_HPP_
# define INCOMPLETEREQUEST_HPP_

#include <stdexcept>
#include <string>

namespace Exception
{
  class IncompleteRequest : public std::runtime_error
  {
  public:
    IncompleteRequest(std::string const& err) throw();
    virtual ~IncompleteRequest() throw();
  };
}


#endif /* !INCOMPLETEREQUEST_HPP_ */
