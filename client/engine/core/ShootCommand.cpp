#include "ShootCommand.hpp"

ShootCommand::ShootCommand()
{
  _time = BigBen::getTimeNow();
}

ShootCommand::~ShootCommand()
{

}

void	ShootCommand::execute()
{
  // change state de la Machine
}

void	ShootCommand::undo()
{

}
