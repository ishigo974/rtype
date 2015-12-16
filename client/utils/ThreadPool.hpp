//
// Created by fourdr_b on 04/11/15.
//

#ifndef BABEL_THREADPOOL_HPP
# define BABEL_THREADPOOL_HPP

# include <queue>
# include <tuple>
# include "ADataPacket.hpp"
# include "Linker.hpp"
# include "SafeQueue.hpp"

template<int ...>
struct seq
{
};

template<int N, int ...S>
struct gens : gens<N - 1, N - 1, S...>
{
};

template<int ...S>
struct gens<0, S...>
{
    typedef seq<S...> type;
};

template<class Ressource, class... Args>
class Task
{
public:
    Task()
    { }

    Task(Linker<void(Ressource, Args...)> const& linker,
         Ressource const& r, int id, Args... args)
            : _linker(linker), _res(r), _id(id)
    {
        _args = std::make_tuple(args...);
    }

    void operator()()
    {
        call(typename gens<sizeof...(Args)>::type());
    }

    template<int ...S>
    void call(seq<S...>)
    {
        auto func = _linker.getLink(_id);
        func(_res, std::get<S>(_args)...);
    }

    Ressource const& getRes() const
    { return _res; }

    void setRes(Ressource res)
    { _res = res; }

    int getId() const
    { return _id; }

    void setId(int id)
    { _id = id; }

private:
    Linker<void(Ressource, Args...)> _linker;
    Ressource                        _res;
    int                              _id;
    std::tuple<Args...>              _args;
};

template<class Resource, class... Args>
class ThreadPool
{
public:
    ThreadPool(Linker<void(Resource, Args...)> const& linker, unsigned int size)
            : _linker(linker), _nbWorkers(size)
    { }

    void schedule(int id, Resource packet, Args... args)
    {
        _processingQueue.push(Task<Resource, Args...>(_linker, packet, id, args...));
    }

    void start()
    {
        for (unsigned int i = 0; i < _nbWorkers; ++i)
        {
            std::thread th(std::bind(&ThreadPool::launch, std::ref(*this)));
            th.detach();
        }
    }

private:
    void launch()
    {
        while (!_processingQueue.isFinished())
        {
            Task<Resource, Args...> tmp;
            _processingQueue.tryPop(&tmp);
            tmp();
        }
    }

private:
    Linker<void(Resource, Args...)>     _linker;
    unsigned int                        _nbWorkers;
    SafeQueue<Task<Resource, Args...> > _processingQueue;
};


#endif //BABEL_THREADPOOL_HPP
