#ifndef INVALIDREQUEST_HPP_
# define INVALIDREQUEST_HPP_

#include <stdexcept>
#include <string>

namespace Exception
{
  class InvalidRequest : public std::runtime_error
  {
  public:
    InvalidRequest(std::string const& err) throw();
    virtual ~InvalidRequest() throw();
  };
}


#endif /* !INVALIDREQUEST_HPP_ */
