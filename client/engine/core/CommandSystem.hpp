#ifndef COMMAND_SYSTEM_HPP_
# define COMMAND_SYSTEM_HPP_

# include <vector>
# include <map>
# include "NetworkSystem.hpp"
# include "ACommand.hpp"
# include "Event.hpp"
# include "EntityManager.hpp"
# include "Input.hpp"
#include "CommandPipeline.hpp"
#include "CommandFactory.hpp"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

class CommandSystem
{
public:
    CommandSystem(EntityManager *entityManager, Input *i, RType::NetworkSystem *ns);
    virtual ~CommandSystem();

    void          processInput();
    void          processNetwork();
    std::string   toString();
    unsigned long getSize() const;
    ACommand      *getByTimestamp(timestamp time);
    void          invalidateCommandAtTimestamp(timestamp time);

private:
    std::vector<ACommand *>                         _commands;
    EntityManager                                   *_entityManager;
    std::map<cu::Event::KeyEvent, ACommand::Action> _actions;
    Input                                           *_input;
    RType::NetworkSystem                            *_ns;
    CommandPipeline                                 _pipeline;
    CommandFactory                                  _factory;
};

#endif /* !COMMAND_SYSTEM_HPP_ */
