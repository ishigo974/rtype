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

        EventType	type;
        union
        {
            KeyEvent	key;
        };
    };
}

#endif		// !EVENT_HPP_
