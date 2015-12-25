#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <queue>
# include "Behaviour.hpp"
# include "ACommand.hpp"
# include "ObjectPool.hpp"
# include "Bullet.hpp"
# include "BulletObject.hpp"
# include "EntityManager.hpp"
# include "Collider.hpp"

class Player : public Behaviour
{
public:
    Player();
    Player(unsigned int _id, std::string const& _name, EntityManager *manager, int hp = 10, int damage = 5);
    virtual ~Player();

    Player(Player const& other);
    Player(Player&& other);
    Player& operator=(Player other);

    bool operator==(Player const& other);
    bool operator!=(Player const& other);
    virtual RTypes::my_uint16_t      getMask() const;
    static const RTypes::my_uint16_t Mask      = ComponentMask::PlayerMask;

    void            setAction(ACommand::Action action);
    virtual void    update(double elapsed);
    virtual int     getDamage() const;
    void            init();
    void            swap(Player& other);
    std::string    toString() const;

protected:
    virtual bool   handleMessage(Collider *o);
    void	       checkDeath();
    void	       checkAvailableBullets();
    void           shoot();
    void           move(double elapsedtime);
    int            getHp() const;

    const std::vector<BulletObject *> &getActiveBullets() const;

protected:
    GameObject                          *_parent;
    int                                 _hp;
    int                                 _damage;
    std::queue<ACommand::Action>        _action;
    bool                                _multiple = false;
    ObjectPool<BulletObject, Bullet>    *_bullets;
    std::vector<BulletObject *>         _activeBullets;
    EntityManager*                      _entityManager;
    Transform*                          _transform;
    double                              _shotTime = 0;
};

#endif /* !PLAYER_HPP_ */
