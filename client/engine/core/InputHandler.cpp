#include "InputHandler.hpp"

InputHandler::InputHandler()
{
  std::cout << "InputHandler created" << std::endl;
}

InputHandler::~InputHandler()
{
}

RTypes::my_uint16_t	InputHandler::getMask() const
{
  return Mask;
}

void	InputHandler::handleInput()
{
}
