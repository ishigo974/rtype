//
// Created by fourdr_b on 05/12/15.
//

#include "State.hpp"

State::State()
{ }

State::State(std::string const& name)
        : _name(name)
{ }

State::State(State const& o)
{
    _name        = o._name;
    _transitions = o._transitions;
}

State::State(State&& o) : State(o)
{
    swap(o);
}

State& State::operator=(State o)
{
    swap(o);

    return (*this);
}

State::~State()
{ }

void State::swap(State& o)
{
    using std::swap;

    swap(_name, o._name);
    swap(_transitions, o._transitions);
}

namespace std
{
    template<>
    inline void swap<State>(State& a, State& b)
    {
        a.swap(b);
    }
}

bool State::canMove(std::string& out)
{
    for (auto&& e : _transitions)
    {
        if (e.second->validate())
        {
            out = e.first;
            return (true);
        }
    }

    return (false);
}

std::string const& State::getName() const
{
    return (_name);
}
