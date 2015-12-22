#ifndef OBJECTPOOL_HPP_
# define OBJECTPOOL_HPP_

# include <queue>

template <typename T, typename U>
class	ObjectPool : Object
{
public:
  ObjectPool(std::string const & name, int layer, EntityManager *manager)
  {
    _entityManager = manager;
    T *obj;
    for (int i = 0; i < 10; ++i)
      {
	obj = _entityManager->createEntity<T>(name, layer, _entityManager);
	_objects.push(obj);
      }
  }

  virtual ~ObjectPool()
  {
    while (!_objects.empty())
      _objects.pop();
  }

  // TODO
  // static void* operator new (size_t size);
  // static void operator delete (void *p);

  T	*create(std::string const & name, int layer)
  {
    T *obj;
    if (_objects.empty())
      obj = _entityManager->createEntity<T>(name, layer, _entityManager);
    else
      {
	obj = _objects.front();
	_objects.pop();
      }
    obj->init();
    return obj;
  }

  void	deleteObject(T *obj)
  {
    obj->deleteObject();
    _objects.push(obj);
  }

  std::queue<T *>	_objects;
private:
  EntityManager		*_entityManager;
};

#endif /* !OBJECTPOOL_HPP_ */
