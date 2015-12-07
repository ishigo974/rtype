//
// Created by fourdr_b on 07/12/15.
//

#include <algorithm>
#include <sstream>
#include "StateMachine.hpp"

StateMachine::StateMachine(State const& initialState)
        : _states{{"S0", initialState}}, _current(_states[initialState.getName()])
{ }

void StateMachine::move()
{
    std::string tmp;

    if (_current.canMove(tmp))
    {
        _current = tmp;
    }
}

void StateMachine::addState(State const& state) throw(std::logic_error)
{
    auto found = std::find_if(_states.begin(), _states.end(), [state](auto &&e)
    {
       return (e.second.getName() == state.getName());
    });
    if (found == _states.end())
    {
        _states[state.getName()] = state;
    }
    else
    {
        std::stringstream err;
        err << "State names must be unique. Trying to create " << state.getName() << " twice";

        throw std::logic_error(err.str());
    }
}
