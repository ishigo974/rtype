#ifndef		SCROLLINGBACKGROUND_HPP_
# define	SCROLLINGBACKGROuND_HPP_

# include	"Behaviour.hpp"

class		ScrollingBackground : public Behaviour
{
public:
  ScrollingBackground();
  ScrollingBackground(unsigned int _id, std::string const& _name);
  ScrollingBackground(ScrollingBackground const& other);
  ScrollingBackground(ScrollingBackground&& other);
  ScrollingBackground& operator=(ScrollingBackground other);
  virtual ~ScrollingBackground();

  bool operator==(ScrollingBackground const& other);
  bool operator!=(ScrollingBackground const& other);

  virtual void update(double elapsedTime);

  virtual RTypes::my_uint16_t getMask() const;

  void swap(ScrollingBackground& other);
};

#endif		// !SCROLLINGBACKGROUND_HPP_
