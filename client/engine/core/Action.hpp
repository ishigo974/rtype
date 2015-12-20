#ifndef ACTION_HPP_
# define ACTION_HPP_

# include "REnums.hpp"
# include "Utils.hpp"

struct Action
{
    Action(ActionType act, MobType mt, MovementType mvt, cu::Position const& p) :
        action(act), mob(mt), movement(mvt), pos(p) {}

    ActionType      action;
    MobType         mob;
    MovementType    movement;
    cu::Position    pos;

    std::string     toString()
    {
        std::stringstream ss;

        ss << mob
           << " " << action
           << " " << movement
           << " " << pos.X()
           << " " << pos.Y();
        return ss.str();
    }
};

#endif // !ACTION_HPP_
