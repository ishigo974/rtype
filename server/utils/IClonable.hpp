#ifndef ICLONABLE_HPP_
# define ICLONABLE_HPP_

# include <string>

class IClonable
{
public:
    virtual ~IClonable() {}

public:
    virtual IClonable*  clone() = 0;
    virtual std::string getName() const = 0;
};

#endif /* ICLONABLE_HPP_ */
