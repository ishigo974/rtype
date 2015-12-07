//
// Created by fourdr_b on 07/12/15.
//

#ifndef RTYPE_TRANSITION_HPP
# define RTYPE_TRANSITION_HPP

# include <tuple>
# include <utility>
# include <functional>

class _Transition
{
public:
    virtual bool validate() = 0;
};

typedef _Transition Transition;

template<class Predicate, class ...Args>
class Transition_ : public _Transition
{
public:
    Transition_()
    { }

    Transition_(Transition_ const& o)
    {
        _pred = o._pred;
        _args = o._args;
    }

    Transition_(Transition_&& o) : Transition_(o)
    {
        swap(o);
    }

    Transition_& operator=(Transition_ o)
    {
        swap(o);

        return (*this);
    }

    Transition_(int id, Predicate pred, Args... args)
            : _pred(pred)
    {
        _args = std::make_tuple(args...);
    }

    template<std::size_t ...I>
    bool call_func(std::index_sequence<I...>)
    {
        return (_pred(std::get<I>(_args)...));
    }

    virtual bool validate()
    {
        return (call_func(std::index_sequence_for<Args...>{}));
    }

    void swap(Transition_& o)
    {
        using std::swap;

        swap(_pred, o._pred);
        swap(_args, o._args);
    }

private:
    std::function<bool(Args...)> _pred;
    std::tuple<Args...>          _args;
};

namespace std
{
    template<class Predicate, class ...Args>
    void swap(Transition_<Predicate, Args...>& a, Transition_<Predicate, Args...>& b)
    {
        a.swap(b);
    }
}

#endif //RTYPE_TRANSITION_HPP
