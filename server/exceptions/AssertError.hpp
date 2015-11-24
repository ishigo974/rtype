#ifndef ASSERTERROR_HPP_
# define ASSERTERROR_HPP_

#include <stdexcept>
#include <string>

namespace Exception
{
  class AssertError : public std::runtime_error
  {
  public:
    AssertError(std::string const& err) throw();
    virtual ~AssertError() throw();
  };
}

#endif /* !ASSERTERROR_HPP_ */
