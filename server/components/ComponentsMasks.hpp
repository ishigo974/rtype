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
            MASK_PLAYER         = 1 << 1
        };
    }
}

#endif /* !COMPONENTSMASKS_HPP_ */
