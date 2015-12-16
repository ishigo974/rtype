#ifndef MOB_HPP_
# define MOB_HPP_

# include "Behaviour.hpp"

class Mob : public Behaviour
{
public:
    Mob();
    Mob(unsigned int _id, std::string const& _name, int hp = 1, int damage = 1, Object *parent = nullptr);
    virtual ~Mob();

    Mob(Mob const& other);
    Mob(Mob&& other);
    Mob& operator=(Mob other);

    bool operator==(Mob const& other);
    bool operator!=(Mob const& other);

    int getHp() const;
    int getDamage() const;

    void         move();
    virtual void update(double elapsedTime);

    void swap(Mob& other);

protected:
    int _hp;
    int _damage;
    int _direction;
};

#endif /* !MOB_HPP_ */
