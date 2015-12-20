#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <queue>
# include "Behaviour.hpp"
# include "ACommand.hpp"
# include "ObjectPool.hpp"
# include "Bullet.hpp"
# include "EntityManager.hpp"

class	Player : public Behaviour
{
public:
  Player();
  Player(unsigned int _id, std::string const& _name, EntityManager *manager, int hp = 100);
  virtual ~Player();

  Player(Player const& other);
  Player(Player&& other);
  Player& operator=(Player other);

  bool operator==(Player const& other);
  bool operator!=(Player const& other);

  int	getHp() const;
  int	getDirection() const;
  void	setAction(ACommand::Action action);

  void		move(Transform & transform);
  virtual void	update(double);

  void swap(Player& other);

  std::string	toString();
  static const RTypes::my_uint16_t Mask = ComponentMask::PlayerMask;
  virtual RTypes::my_uint16_t	getMask() const;

protected:
  int				_hp;
  std::queue<ACommand::Action>	_action;
  bool				_multiple = false;
  ObjectPool<Bullet>		_bullets;
  std::vector<Bullet *>		_activeBullets;
  EntityManager			*_entityManager;
};

#endif /* !PLAYER_HPP_ */
