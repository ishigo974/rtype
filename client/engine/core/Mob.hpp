#ifndef MOB_HPP_
# define MOB_HPP_

# include "Behaviour.hpp"
# include "Transform.hpp"

class Mob : public Behaviour
{
public:
    Mob();
  Mob(unsigned int _id, std::string const& _name, int hp = 1, int damage = 1, int type = 0);
    virtual ~Mob();

    Mob(Mob const& other);
    Mob(Mob&& other);
    Mob& operator=(Mob other);

    bool operator==(Mob const& other);
    bool operator!=(Mob const& other);

    int getHp() const;
    int getDamage() const;

    void         move();
    virtual void update(double);

    void swap(Mob& other);

  std::string	toString() const;

protected:
    int _hp;
    int _damage;
    int _direction;
  int	_type;
  int	_graphicHeight;
  Transform	*_transform;
};

#endif /* !MOB_HPP_ */
