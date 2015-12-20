#ifndef OBJECTPOOL_HPP_
# define OBJECTPOOL_HPP_

template <typename T>
class	ObjectPool
{
public:
  ObjectPool() {}
  virtual ~ObjectPool() {}

  void	create();

private:
  T			*_objects[40];
  static const int	_size = 40;
};

#endif /* !OBJECTPOOL_HPP_ */
