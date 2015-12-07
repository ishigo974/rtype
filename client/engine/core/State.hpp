//
// Created by fourdr_b on 05/12/15.
//

#ifndef RTYPE_STATE_HPP
# define RTYPE_STATE_HPP

# include <string>
# include <memory>
# include <map>
# include "Transition_.hpp"

class State
{
public:
    State();
    State(std::string const& name);

    State(State const& o);
    State(State&& o);

    State& operator=(State o);

    ~State();

    void swap(State& o);

    template<class Predicate, class ...Args>
    void addTransition(Predicate p, Args ...args, std::string const& state)
    {
        _transitions[state] = std::make_unique<Transition>(p, args...);
    };

    bool canMove(std::string& out);

protected:
    std::string                                         _name;
    std::map<std::string, std::unique_ptr<Transition> > _transitions;
};


#endif //RTYPE_STATE_HPP
