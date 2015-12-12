#include "MoveCommand.hpp"

MoveCommand::MoveCommand(Direction direction)
{
  _direction = direction;
  _time = BigBen::getTimeNow();
}

MoveCommand::~MoveCommand()
{
}

void	MoveCommand::execute()
{
}

void	MoveCommand::undo()
{

}
