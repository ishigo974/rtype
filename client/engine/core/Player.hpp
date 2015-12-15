#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <queue>
# include "Behaviour.hpp"
# include "ACommand.hpp"

class	Player : public Behaviour
{
public:
  Player();
  Player(unsigned int _id, std::string const& _name, int hp = 100, int damage = 1, Object* parent = nullptr);
  virtual ~Player();

  Player(Player const& other);
  Player(Player&& other);
  Player& operator=(Player other);

  bool operator==(Player const& other);
  bool operator!=(Player const& other);

  int	getHp() const;
  int	getDamage() const;
  int	getDirection() const;
  void	setAction(ACommand::Action action);

  void		move();
  virtual void	update(double elapsedTime);

  void swap(Player& other);

  static const RTypes::my_uint16_t Mask = ComponentMask::PlayerMask;
  virtual RTypes::my_uint16_t	getMask() const;

protected:
  int				_hp;
  int				_damage;
  std::queue<ACommand::Action>	_action;
};

#endif /* !PLAYER_HPP_ */
