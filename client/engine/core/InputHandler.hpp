#ifndef INPUT_HANDLER_HPP_
# define INPUT_HANDLER_HPP_

# include "ACommand.hpp"
# include "Behaviour.hpp"
# include "Event.hpp"

class	InputHandler : public Behaviour
{
public:
  InputHandler();
  virtual ~InputHandler();

  virtual RTypes::my_uint16_t	getMask() const;
  virtual void			handleInput();

  static RTypes::my_uint16_t const Mask = ComponentMask::InputHandlerMask;
};

#endif /* !INPUT_HANDLER_HPP_ */
