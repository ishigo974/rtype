#ifndef __NOTIMPLEMENTED_HPP__
# define __NOTIMPLEMENTED_HPP__

#include <stdexcept>
#include <string>

namespace Exception
{
  class NotImplemented : public std::runtime_error
  {
  public:
    NotImplemented(std::string const& err) throw();
    virtual ~NotImplemented() throw();
  };
}


#endif /* !__NOTIMPLEMENTED_HPP__ */
