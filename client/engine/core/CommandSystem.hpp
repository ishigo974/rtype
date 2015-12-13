#ifndef COMMAND_SYSTEM_HPP_
# define COMMAND_SYSTEM_HPP_

# include <vector>
# include <map>
# include "ACommand.hpp"
# include "Event.hpp"
# include "EntityManager.hpp"
# include "Input.hpp"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

class CommandSystem
{
public:

    CommandSystem(EntityManager *entityManager, Input *i);
    virtual ~CommandSystem();

    void        addCommand();
    std::string toString();
    int         getSize() const;
    ACommand    *getByTimestamp(timestamp time);
    void        invalidateCommandAtTimestamp(timestamp time);

private:
    std::vector<ACommand *>                         _commands;
    EntityManager                                   *_entityManager;
    std::map<cu::Event::KeyEvent, ACommand::Action> _actions;
    Input                                           *_input;
};

#endif /* !COMMAND_SYSTEM_HPP_ */
