#ifndef ISTRINGABLE_HPP_
# define ISTRINGABLE_HPP_

# include <string>
# include <ostream>

class IStringable
{
public:
    virtual ~IStringable()
    { }

public:
    virtual std::string toString() const = 0;
};

std::ostream& operator<<(std::ostream& lhs, IStringable const& rhs);

#endif /* !ISTRINGABLE_HPP_ */
