#ifndef ACTION_HPP_
# define ACTION_HPP_

# include "REnums.hpp"
# include "Utils.hpp"

struct Action
{
    Action(MobType mt, MovementType mvt, cu::Position const& p) :
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

#endif // !ACTION_HPP_
