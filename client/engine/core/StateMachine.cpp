//
// Created by fourdr_b on 07/12/15.
//

#include "StateMachine.hpp"

StateMachine::StateMachine(State const& initialState)
        : _states{{"S0", initialState}}, _current(_states.begin()->second)
{ }

void StateMachine::move()
{
    std::string tmp;

    for (auto e : _states)
    {
        if (e.second.canMove(tmp))
        {
            _current = _states[tmp];
        }
    }
}
