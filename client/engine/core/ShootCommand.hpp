#ifndef RTYPE_SHOOTCOMMAND_HPP_
# define RTYPE_SHOOTCOMMAND_HPP_

# include "ACommand.hpp"

class	ShootCommand : public ACommand
{
public:
    ShootCommand(EntityManager *entityManager);
    virtual ~ShootCommand();

    virtual void	execute();
    virtual void	undo();
};

#endif /* !RTYPE_SHOOTCOMMAND_HPP_ */
