#ifndef IMONITORABLE_HPP_
# define IMONITORABLE_HPP_

# include "NetTypes.hpp"

class IMonitorable
{
public:
    virtual ~IMonitorable()
    { }

public:
    virtual rSocket getSocket() const = 0; //TODO typedef
};

#endif /* !IMONITORABLE_HPP_ */
