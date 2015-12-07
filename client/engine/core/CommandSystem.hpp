#ifndef COMMAND_SYSTEM_HPP_
# define COMMAND_SYSTEM_HPP_

# include <queue>
# include "ACommand.hpp"

class CommandSystem
{
public:
  CommandSystem();
  virtual ~CommandSystem();

  // void	addCommand(cu::Event event);

private:
  std::queue<ACommand *>	_commands;
};

#endif /* !COMMAND_SYSTEM_HPP_ */
