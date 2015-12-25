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
        DOWN,
        LEFT,
        RIGHT,
        SHOOT
    };

    void setObject(GameObject *obj)
    {
        _obj = obj;
    }

    virtual std::chrono::microseconds getTime()
    {
        return _time;
    }

protected:
    std::chrono::microseconds _time;
    GameObject                *_obj;
    EntityManager             *_entityManager;
};

#endif /* !RTYPE_ACOMMAND_HPP_ */
