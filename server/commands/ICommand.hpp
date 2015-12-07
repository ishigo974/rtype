#ifndef ICOMMAND_HPP_
# define ICOMMAND_HPP_

# include "IClonable.hpp"
# include "IStringable.hpp"

class ICommand : public IStringable
{
public:
    virtual ~ICommand() {}

public:
    virtual void    execute() = 0;
    virtual void    undo() = 0;
};

#endif /* !ICOMMAND_HPP_ */
