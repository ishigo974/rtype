#ifndef INPUT_HANDLER_HPP_
# define INPUT_HANDLER_HPP_

# include "ACommand.hpp"

class	InputHandler : public Behaviour
{
public:
  virtual ~InputHandler() { }

  virtual RTypes::my_uint16_t	getMask() const = 0;
  virtual void			handleInput(int input) = 0;

  static RTypes::my_uint16_t const Mask = 256;
};

#endif /* !INPUT_HANDLER_HPP_ */
