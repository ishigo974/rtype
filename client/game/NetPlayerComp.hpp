#ifndef RTYPE_NETPLAYERCOMP_HPP
# define RTYPE_NETPLAYERCOMP_HPP

# include <Transform.hpp>
# include <EntityManager.hpp>
# include <BulletObject.hpp>
# include <Bullet.hpp>
# include <ObjectPool.hpp>
# include <UDPView.hpp>
# include "Component.hpp"

class NetPlayerComp : public Behaviour
{
public:
    NetPlayerComp();
    NetPlayerComp(unsigned int id, std::string const& name, EntityManager *em, int hp, int dmg);
    NetPlayerComp(NetPlayerComp& o);
    NetPlayerComp(NetPlayerComp&& o);
    NetPlayerComp& operator=(NetPlayerComp& o);

    virtual ~NetPlayerComp();

    void swap(NetPlayerComp& o);

public:
    void         init();
    virtual void update(double elapsedTime);

public:
    virtual bool                     handleMessage(Collider *o);
    void                             checkDeath();
    void                             checkAvailableBullets();
    void                             shoot();
    void                             move(double elapsedtime,
                                          RType::InGameEvent action);
    int                              getHp() const;

private:
    GameObject*     _parent;
    int             _hp;
    int             _damage;
    bool            _multiple    = false;

    ObjectPool<BulletObject, Bullet>*   _bullets;
    std::vector<BulletObject *>         _activeBullets;

    EntityManager*  _em;
    Transform*      _transform;
    double          _shotTime = 0;
    UDPView*        _udp;
};


#endif //RTYPE_NETPLAYERCOMP_HPP
