#include "MoveCommand.hpp"

MoveCommand::MoveCommand(Direction direction)
{
  _direction = direction;
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
