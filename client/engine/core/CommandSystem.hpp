#ifndef COMMAND_SYSTEM_HPP_
# define COMMAND_SYSTEM_HPP_

# include <queue>
# include "ACommand.hpp"
# include "Event.hpp"

class CommandSystem
{
public:
  CommandSystem();
  virtual ~CommandSystem();

  void		addCommand(cu::Event event);
  std::string	toString();
  int		getSize() const;

private:
  std::queue<ACommand *>	_commands;
};

#endif /* !COMMAND_SYSTEM_HPP_ */
