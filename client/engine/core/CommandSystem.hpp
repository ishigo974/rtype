#ifndef COMMAND_SYSTEM_HPP_
# define COMMAND_SYSTEM_HPP_

# include <queue>
# include "ACommand.hpp"
# include "Event.hpp"
# include "EntityManager.hpp"

class CommandSystem
{
public:
  CommandSystem(EntityManager *entityManager);
  virtual ~CommandSystem();

  void		addCommand(cu::Event event);
  std::string	toString();
  void		process();
  int		getSize() const;

private:
  std::queue<ACommand *>	_commands;
  EntityManager			*_entityManager;
};

#endif /* !COMMAND_SYSTEM_HPP_ */
