#ifndef OBJECTPOOL_HPP_
# define OBJECTPOOL_HPP_

# include <queue>

template <typename T, typename U>
class	ObjectPool : Object
{
public:
  ObjectPool(EntityManager *manager)
  {
    _entityManager = manager;
  }
  virtual ~ObjectPool() { }

  // TODO
  // static void* operator new (size_t size);
  // static void operator delete (void *p);

  T	*create(std::string const & name, int layer)
  {
    T *obj;
    if (_objects.empty())
      {
	obj = _entityManager->createEntity<T>(name, layer, _entityManager);
      }
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

private:
  EntityManager		*_entityManager;
  std::queue<T *>	_objects;
};

#endif /* !OBJECTPOOL_HPP_ */
