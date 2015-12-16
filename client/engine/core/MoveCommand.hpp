#ifndef RTYPE_MOVECOMMAND_HPP_
# define RTYPE_MOVECOMMAND_HPP_

# include "ACommand.hpp"

class	MoveCommand : public ACommand
{
public:
  MoveCommand(EntityManager *entityManager, ACommand::Action direction);
  virtual ~MoveCommand();

  virtual void	execute();
  virtual void	undo();

private:
  ACommand::Action	_direction;
};

#endif /* !RTYPE_MOVECOMMAND_HPP_ */
