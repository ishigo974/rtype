#ifndef BULLET_HPP_
# define BULLET_HPP_

# include "Behaviour.hpp"
# include "Transform.hpp"
# include "GameObject.hpp"

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
    virtual int getDamage() const;
    void	setHp(int hp);
    void    setDamage(int damage);
    virtual void update(double elapsedTime);

    void swap(Bullet& other);

    void	setX(float x);
    void	setY(float y);
    float	getX() const;
    float	getY() const;
    void	setDirection(Bullet::Direction d);
    std::string	toString() const;
    bool	getAvailable() const;
    void	setAvailable(bool a);
    void    init();

    virtual bool handleMessage(Collider *o);

protected:
    void         move(double elapsedTime) const;

protected:
    int                 _hp;
    int                 _damage;
    Bullet::Direction	_direction;
    Transform		    *_transform;
    GameObject          *_parent;
    bool		     	_available;
};

#endif /* !BULLET_HPP_ */
