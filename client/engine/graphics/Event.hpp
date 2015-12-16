#ifndef		EVENT_HPP_
# define	EVENT_HPP_

namespace cu
{
  struct		Event
  {
    enum EventType
      {
	KeyPressed,
	KeyReleased,
	MouseButtonPressed,
	MouseButtonReleased,
	Closed,
	None
      };

    enum KeyEvent
      {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	SHOOT,
	ESCAPE,
	LAST_ACTION
      };

    enum MouseButton
      {
	LMB,
	RMB,
	MMB
      };

    struct MouseButtonEvent
      {
	MouseButton button;
	int x;
	int y;
      };
    
    EventType	type;
    union
    {
      KeyEvent	key;
      MouseButtonEvent mouse;
    };
  };
}

#endif		// !EVENT_HPP_
