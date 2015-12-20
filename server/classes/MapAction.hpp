#ifndef ACTION_HPP_
# define ACTION_HPP_

# include "MobEnums.hpp"
# include "Utils.hpp"

namespace RType
{
    namespace Map
    {
        struct Action
        {
            enum Type : uint16_t
            {
                Spawn = 0
            };

            Action(Type act, MobType mt, MovementType mvt, cu::Position const& p) :
                action(act), mob(mt), movement(mvt), pos(p) {}

            Type            action;
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
    }
}

#endif // !ACTION_HPP_
