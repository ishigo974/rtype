#ifndef RTYPE_ACOMMAND_HPP_
# define RTYPE_ACOMMAND_HPP_

# include <chrono>
# include "GameObject.hpp"
# include "BigBen.hpp"
# include "EntityManager.hpp"

class ACommand
{
public:
    virtual ~ACommand()
    { }

    virtual void execute() = 0;
    virtual void undo()    = 0;

public:
    enum Action
    {
        DEFAULT = -1,
        UP,
        UP_RIGHT,
        UP_LEFT,
        DOWN,
        DOWN_RIGHT,
        DOWN_LEFT,
        LEFT,
        RIGHT,
        SHOOT
    };

    void setObject(GameObject *obj)
    {
        _obj = obj;
    }

    virtual std::chrono::time_point<std::chrono::high_resolution_clock> getTime()
    {
        return _time;
    }

protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> _time;
    GameObject                                                  *_obj;
    EntityManager                                               *_entityManager;
};

#endif /* !RTYPE_ACOMMAND_HPP_ */
