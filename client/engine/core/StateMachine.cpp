#include <algorithm>
#include <sstream>
#include "StateMachine.hpp"

StateMachine::StateMachine(unsigned int id, State const& initialState) :
        _states{{initialState.getName(), initialState}},
        _id(id),
        _current(_states[initialState.getName()])
{ }

StateMachine::~StateMachine()
{

}

void StateMachine::move()
{
    std::string tmp;

    if (_current.canMove(tmp))
    {
        _current = tmp;
    }
}

void StateMachine::addState(State const& state)
{
    auto found = std::find_if(_states.begin(), _states.end(), [state](auto&& e)
    {
        return (e.second.getName() == state.getName());
    });
    if (found == _states.end())
    {
        _states[state.getName()] = state;
    }
    else
    {
        std::string str;
        str = std::string("State names must be unique. Trying to create ").append(state.getName());

        throw std::logic_error(str);
    }
}

State const& StateMachine::getCurrent() const
{
    return (_current);
}

RTypes::my_uint16_t StateMachine::getMask() const
{
    return Mask;
}
