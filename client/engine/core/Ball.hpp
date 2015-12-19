#ifndef BALL_HPP_
# define BALL_HPP_

# include "Behaviour.hpp"
# include "Transform.hpp"

class Ball : public Behaviour
{
public:
    Ball();
  Ball(unsigned int _id, std::string const& _name, int hp = 1, int damage = 1);
    virtual ~Ball();

    Ball(Ball const& other);
    Ball(Ball&& other);
    Ball& operator=(Ball other);

    bool operator==(Ball const& other);
    bool operator!=(Ball const& other);

    int getHp() const;
    int getDamage() const;

    void         move();
    virtual void update(double elapsedTime);

    void swap(Ball& other);

  void	setX(float x);
  void	setY(float y);

protected:
    int _hp;
    int _damage;
};

#endif /* !BALL_HPP_ */
