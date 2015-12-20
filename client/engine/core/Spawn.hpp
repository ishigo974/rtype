#ifndef SPAWN_HPP_
# define SPAWN_HPP_

# include "REnums.hpp"
# include "Utils.hpp"

struct Spawn
{
    Spawn(MobType mt, MovementType mvt, cu::Position const& p) :
        mob(mt), movement(mvt), pos(p) {}

    MobType         mob;
    MovementType    movement;
    cu::Position    pos;

    std::string     toString()
    {
        std::stringstream ss;

        ss << mob
           << " " << movement
           << " " << pos.X()
           << " " << pos.Y();
        return ss.str();
    }
};

#endif // !SPAWN_HPP_
