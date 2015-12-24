#ifndef MOBSPAWNER_HPP_
# define MOBSPAWNER_HPP_

# include "Behaviour.hpp"
# include "ObjectPool.hpp"
# include "RTypeGame.hpp"
# include "Mob.hpp"
# include "MobObject.hpp"
# include "MobObject.hpp"
# include "Mob.hpp"
# include "Component.hpp"
# include "IMobType.hpp"
# include "RTypeGame.hpp"
# include "UDPView.hpp"

class MobSpawner : public Behaviour
{
public:
    MobSpawner();
    MobSpawner(unsigned int _id, std::string const& _name,
               EntityManager *manager, RTypeGame::MobTypeMap *mobTypes);
    virtual ~MobSpawner();

public:
    MobSpawner(MobSpawner const& other);
    MobSpawner(MobSpawner&& other);
    MobSpawner& operator=(MobSpawner other);

public:
    bool operator==(MobSpawner const& other);
    bool operator!=(MobSpawner const& other);

public:
    void                            swap(MobSpawner& other);
    virtual void                    update(double);
    virtual RTypes::my_uint16_t     getMask() const;
    void                            init();

protected:
    void                            spawnMob(unsigned int id);

public:
    static const RTypes::my_uint16_t Mask   = ComponentMask::MobSpawnerMask;

protected:
    ObjectPool<MobObject, Mob>*   _mobs;
    std::vector<MobObject *>      _activeMobs;
    EntityManager*                _entityManager;
    RTypeGame::MobTypeMap*        _mobTypes;
    UDPView*                      _udpView;
    GameObject*                   _parent;
};

#endif /* !MOBSPAWNER_HPP_ */
