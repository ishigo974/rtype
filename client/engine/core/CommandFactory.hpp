//
// Created by fourdr_b on 24/12/15.
//

#ifndef RTYPE_COMMANDFACTORY_HPP
# define RTYPE_COMMANDFACTORY_HPP

# include "ACommand.hpp"
# include "InGameEvent.hpp"
#include "GameManager.hpp"

class CommandFactory
{
public:
    CommandFactory(GameManager *gm);
public:
    ACommand *createCommand(RType::InGameEvent const& event);

private:
    GameManager *_gm;
};


#endif //RTYPE_COMMANDFACTORY_HPP
