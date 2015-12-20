#ifndef BULLET_OBJECT_HPP_
# define BULLET_OBJECT_HPP_

# include "GameObject.hpp"
# include "EntityManager.hpp"

class	BulletObject : public GameObject
{
public:
  BulletObject();
  BulletObject(unsigned int _id, std::string const& _name, int _layer, EntityManager *manager = nullptr);
  virtual ~BulletObject();

  BulletObject(unsigned int _id, std::string const& _name, int _layer);

  BulletObject(BulletObject const& other);
  BulletObject(BulletObject&& other);
  BulletObject& operator=(BulletObject other);

  virtual bool operator==(BulletObject const& other);
  virtual bool operator!=(BulletObject const& other);

  std::string	toString() const;

  void init();
  void deleteObject();
  void swap(BulletObject& other);

private:
  EntityManager	*_entityManager;
};

#endif /* !BULLET_OBJECT_HPP_ */
