#ifndef PLAYER_OBJECT_HPP_
# define PLAYER_OBJECT_HPP_

# include "GameObject.hpp"
# include "EntityManager.hpp"

class	PlayerObject : public GameObject
{
public:
  PlayerObject();
  PlayerObject(unsigned int _id, std::string const& _name, int _layer, EntityManager *manager = nullptr);
  virtual ~PlayerObject();

  PlayerObject(unsigned int _id, std::string const& _name, int _layer);

  PlayerObject(PlayerObject const& other);
  PlayerObject(PlayerObject&& other);
  PlayerObject& operator=(PlayerObject other);

  virtual bool operator==(PlayerObject const& other);
  virtual bool operator!=(PlayerObject const& other);

  std::string	toString() const;

  void init();
  void swap(PlayerObject& other);

private:
  EntityManager	*_entityManager;
};

#endif /* !PLAYER_OBJECT_HPP_ */
