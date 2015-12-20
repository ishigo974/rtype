#ifndef RTYPE_RENUMS_HPP
# define RTYPE_RENUMS_HPP

# include "RTypes.hpp"

enum ComponentMask : RTypes::my_uint16_t
{
    DefaultMask      = 0,
    BehaviourMask    = 2,
    ColliderMask     = 4,
    StateMachineMask = 8,
    PlayerMask       = 16,
    BulletMask       = 32,
    GUIManagerMask   = 64,
    DrawableMask     = 128
};

enum MobType : RTypes::my_uint16_t
{
    Retarded = 0,
    Noob = 1,
    Average = 2,
    Skilled = 3,
    Pro = 4,
    GodLike = 5,
    Flff = 9001
};

enum MovementType : RTypes::my_uint16_t
{
    Straight = 0,
    DiagonalUp = 1,
    DiagonalDown = 2,
    UpAndDown = 3
};

#endif //RTYPE_RENUMS_HPP
