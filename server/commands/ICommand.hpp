#ifndef ICOMMAND_HPP_
# define ICOMMAND_HPP_

class ICommand
{
public:
    virtual ~ICommand() {}

public:
    virtual void    execute() = 0;
    virtual void    undo() = 0;
};

#endif /* !ICOMMAND_HPP_ */
