#ifndef __GENERATETYPEERROR_HPP__
# define __GENERATETYPEERROR_HPP__

#include <stdexcept>
#include <string>

namespace Exception
{
  class GenerateTypeError : public std::runtime_error
  {
  public:
    GenerateTypeError(std::string const& err) throw();
    virtual ~GenerateTypeError() throw();
  };
}


#endif /* !__GENERATETYPEERROR_HPP__ */
