#ifndef IMONITORABLE_HPP_
# define IMONITORABLE_HPP_

class IMonitorable
{
public:
  virtual ~IMonitorable() {}

public:
  virtual int       getSocket() const = 0; //TODO typedef
};

#endif /* !IMONITORABLE_HPP_ */
