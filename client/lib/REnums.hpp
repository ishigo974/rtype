//
// Created by naliwe on 07/12/15.
//

#ifndef RTYPE_RENUMS_HPP
# define RTYPE_RENUMS_HPP

# include "RTypes.hpp"

enum ComponentMask : RTypes::my_uint16_t
{
    DefaultMask      = 0,
    BehaviourMask    = 2,
    ColliderMask     = 4,
    StateMachineMask = 8,
    DrawableMask     = 128,
    InputHandlerMask = 256
};

#endif //RTYPE_RENUMS_HPP
