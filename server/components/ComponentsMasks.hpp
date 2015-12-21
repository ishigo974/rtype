#ifndef COMPONENTSMASKS_HPP_
# define COMPONENTSMASKS_HPP_

# include "ComponentMask.hpp"

namespace RType
{
    namespace Component
    {
        enum Masks
        {
            MASK_NETWORKTCP     = 1,
            MASK_PLAYER         = 1 << 1,
            MASK_ROOM           = 1 << 2,
            MASK_NETWORKUDP     = 1 << 3,
            MASK_POSITION       = 1 << 4,
            MASK_SHOT           = 1 << 5,
            MASK_SHIP           = 1 << 6,
            MASK_MOB            = 1 << 7
        };
    }
}

#endif /* !COMPONENTSMASKS_HPP_ */
