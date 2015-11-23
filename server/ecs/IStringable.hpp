#ifndef ISTRINGABLE_HPP_
# define ISTRINGABLE_HPP_

# include <string>

class IStringable
{
  virtual std::string     toString() const = 0;
};

#endif /* !ISTRINGABLE_HPP_ */
