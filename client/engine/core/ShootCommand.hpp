#ifndef RTYPE_SHOOTCOMMAND_HPP_
# define RTYPE_SHOOTCOMMAND_HPP_

# include "ACommand.hpp"

class	ShootCommand : public ACommand
{
public:
    ShootCommand(EntityManager *entityManager, std::chrono::microseconds time);
    virtual ~ShootCommand();

    virtual void	execute();
    virtual void	undo();
};

#endif /* !RTYPE_SHOOTCOMMAND_HPP_ */
