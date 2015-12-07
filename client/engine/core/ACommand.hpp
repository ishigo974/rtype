#ifndef RTYPE_ACOMMAND_HPP_
# define RTYPE_ACOMMAND_HPP_

# include <chrono>
# include "GameObject.hpp"

class ACommand
{
public:
  virtual ~ACommand() {}

  virtual void	execute() = 0;
  virtual void	undo() = 0;

protected:
  std::chrono::time_point<std::chrono::high_resolution_clock>	_time;
};

#endif /* !RTYPE_ACOMMAND_HPP_ */
