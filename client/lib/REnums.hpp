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
    DrawableMask     = 128,
    TCPMask          = 256,
    UDPMask          = 512,
    MobMask          = 1024,
    SoundMask        = 2048,
    MobSpawnerMask      = 4096,
};

#endif //RTYPE_RENUMS_HPP
