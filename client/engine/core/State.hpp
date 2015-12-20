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
    explicit State(std::string const& name);

    State(State const& o);
    State(State&& o);

    State& operator=(State o);

    ~State();

    void swap(State& o);

    template<class Predicate, class ...Args>
    void addTransition(std::string const& state, Predicate p, Args ...args)
    {
        _transitions[state] = std::make_shared<Transition_<Predicate, Args...> >(p, args...);
    };

    bool canMove(std::string& out);

    std::string const& getName() const;

protected:
    std::string                                         _name;
    std::map<std::string, std::shared_ptr<Transition> > _transitions;
};


#endif //RTYPE_STATE_HPP
