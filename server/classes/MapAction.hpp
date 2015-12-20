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

            Action(Type act, MobType mt, MovementType mvt,
                   cu::Position const& p) :
                    action(act), mob(mt), movement(mvt), pos(p)
            { }

            Type         action;
            MobType      mob;
            MovementType movement;
            cu::Position pos;

            std::string toString() const
            {
                std::string ss;

                ss += mob;
                ss += " ";
                ss += action;
                ss += " ";
                ss += movement;
                ss += " ";
                ss += pos.X();
                ss += " ";
                ss += pos.Y();
                return ss;
            }
        };
    }
}

#endif // !ACTION_HPP_
