#ifndef RTYPE_STATEMACHINE_HPP
# define RTYPE_STATEMACHINE_HPP

# include "State.hpp"
# include "Component.hpp"

class StateMachine
{
public:
    static const RTypes::my_uint16_t Mask = ComponentMask::StateMachineMask;

public:
    StateMachine(State const& initialState);
    virtual ~StateMachine();

    void move();
    void addState(State const& state);

    virtual RTypes::my_uint16_t getMask() const;

    State const& getCurrent() const;

private:
    std::map<std::string, State> _states;
    State&                       _current;
};


#endif //RTYPE_STATEMACHINE_HPP
