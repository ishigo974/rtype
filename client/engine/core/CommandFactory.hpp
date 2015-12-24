//
// Created by fourdr_b on 24/12/15.
//

#ifndef RTYPE_COMMANDFACTORY_HPP
# define RTYPE_COMMANDFACTORY_HPP

# include "ACommand.hpp"
# include "InGameEvent.hpp"
# include "EntityManager.hpp"
# include "GameManager.hpp"

class CommandFactory
{
public:
    CommandFactory(EntityManager *em);
public:
    ACommand *createCommand(RType::InGameEvent const& event);

private:
    GameManager   *_gm;
    EntityManager *_em;
};


#endif //RTYPE_COMMANDFACTORY_HPP
