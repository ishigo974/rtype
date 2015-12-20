#ifndef BULLET_HPP_
# define BULLET_HPP_

# include "Behaviour.hpp"
# include "Transform.hpp"

class Bullet : public Behaviour
{
public:

  enum Direction
    {
      LEFT = -1,
      DEFAULT = 0,
      RIGHT = 1
    };

public:
    Bullet();
  Bullet(unsigned int _id, std::string const& _name);
    virtual ~Bullet();

    Bullet(Bullet const& other);
    Bullet(Bullet&& other);
    Bullet& operator=(Bullet other);

    bool operator==(Bullet const& other);
    bool operator!=(Bullet const& other);

    int getHp() const;
    int getDamage() const;

    void         move();
    virtual void update(double elapsedTime);

    void swap(Bullet& other);

  void	setX(float x);
  void	setY(float y);
  float	getX();
  float	getY();
  void	setDirection(Bullet::Direction d);
  std::string	toString();
  void	create();
  void	deleteObj();
  bool	getAvailable() const;
  void	setAvailable(bool a);

  static const RTypes::my_uint16_t Mask = ComponentMask::BulletMask;
  virtual RTypes::my_uint16_t	getMask() const;

protected:
    int _hp;
    int _damage;
  Bullet::Direction	_direction;
  // Transform		*_transform;
  bool			_available;
};

#endif /* !BULLET_HPP_ */
