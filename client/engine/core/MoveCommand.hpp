#ifndef RTYPE_MOVECOMMAND_HPP_
# define RTYPE_MOVECOMMAND_HPP_

# include "ACommand.hpp"

class	MoveCommand : public ACommand
{
public:
  enum Direction
    {
      UP = 0,
      DOWN,
      LEFT,
      RIGHT
    };

public:
  MoveCommand(Direction direction);
  virtual ~MoveCommand();

  virtual void	execute();
  virtual void	undo();

private:
  Direction	_direction;
};

#endif /* !RTYPE_MOVECOMMAND_HPP_ */
