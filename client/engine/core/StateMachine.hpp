//
// Created by fourdr_b on 07/12/15.
//

#ifndef RTYPE_STATEMACHINE_HPP
# define RTYPE_STATEMACHINE_HPP

# include "State.hpp"

class StateMachine
{
public:
    StateMachine(State const& initialState);

    void move();

private:
    std::map<std::string, State> _states;
    State& _current;
};


#endif //RTYPE_STATEMACHINE_HPP
