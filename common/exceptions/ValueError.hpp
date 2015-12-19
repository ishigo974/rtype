#ifndef VALUEERROR_HPP_
# define VALUEERROR_HPP_

#include <stdexcept>
#include <string>

namespace Exception
{
  class ValueError : public std::runtime_error
  {
  public:
    ValueError(std::string const& err) throw();
    virtual ~ValueError() throw();
  };
}


#endif /* !VALUEERROR_HPP_ */
