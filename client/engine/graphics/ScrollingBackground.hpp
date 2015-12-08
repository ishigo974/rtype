#ifndef		SCROLLINGBACKGROUND_HPP_
# define	SCROLLINGBACKGROuND_HPP_

# include	"Behaviour.hpp"

class		ScrollingBackground : public Behaviour
{
public:
  ScrollingBackground();
  ScrollingBackground(unsigned int _id, std::string const& _name, unsigned int speed,
		      Object *parent);
  ScrollingBackground(ScrollingBackground const& other);
  ScrollingBackground(ScrollingBackground&& other);
  ScrollingBackground& operator=(ScrollingBackground other);
  virtual ~ScrollingBackground();

  bool operator==(ScrollingBackground const& other);
  bool operator!=(ScrollingBackground const& other);

  virtual void update(double elapsedTime);

  void swap(ScrollingBackground& other);

private:
  unsigned int	_speed;
};

#endif		// !SCROLLINGBACKGROUND_HPP_
