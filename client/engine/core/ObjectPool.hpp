#ifndef OBJECTPOOL_HPP_
# define OBJECTPOOL_HPP_

template <typename T>
class	ObjectPool : Object
{
public:
  ObjectPool() { }
  virtual ~ObjectPool() { }

  // static void* operator new (size_t size);
  // static void operator delete (void *p);

  void	init()
  {
    T *obj = new T;
    _objects.push(obj);
  }

  T	*create()
  {
    if (_objects.empty())
      {
	T *obj = new T;
	obj->create();
	return obj;
      }
    else
      {
	T *obj = _objects.front();
	_objects.pop();
	return obj;
      }
  }

  void	deleteObject(T *obj)
  {
    obj->deleteObj();
    _objects.push(obj);
  }

  std::queue<T *>	_objects;	
private:
};

#endif /* !OBJECTPOOL_HPP_ */
