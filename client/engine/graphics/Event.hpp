#ifndef		EVENT_HPP_
# define	EVENT_HPP_

# include "RTypes.hpp"

namespace cu
{
    struct    Event
    {
        enum EventType
        {
            KeyPressed,
            KeyReleased,
            MouseButtonPressed,
            MouseButtonReleased,
            TextEntered,
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

        struct TextEnteredEvent
        {
            RTypes::my_uint32_t unicode;
        };

        EventType	type;
        union
        {
            KeyEvent            key;
            MouseButtonEvent    mouse;
            TextEnteredEvent    text;
        };
    };
}

#endif		// !EVENT_HPP_
