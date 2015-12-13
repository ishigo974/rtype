#ifndef COMMAND_SYSTEM_HPP_
# define COMMAND_SYSTEM_HPP_

# include <vector>
# include <map>
# include "ACommand.hpp"
# include "Event.hpp"
# include "EntityManager.hpp"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

class CommandSystem
{
public:

    CommandSystem(EntityManager *entityManager);
    virtual ~CommandSystem();

    void        addCommand(cu::Event event);
    std::string toString();
    int         getSize() const;
    ACommand    *getByTimestamp(timestamp time);
    void        invalidateCommandAtTimestamp(timestamp time);

private:
    std::vector<ACommand *>                         _commands;
    EntityManager                                   *_entityManager;
    std::map<cu::Event::KeyEvent, bool>             _statuses;
    std::map<cu::Event::KeyEvent, ACommand::Action> _actions;
};

#endif /* !COMMAND_SYSTEM_HPP_ */
