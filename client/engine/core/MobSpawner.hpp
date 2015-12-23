#ifndef MOBSPAWNER_HPP_
# define MOBSPAWNER_HPP_

# include "Behaviour.hpp"
# include "ObjectPool.hpp"
# include "MobSpawner.hp"
# include "Mob.hpp"

class MobSpawner : public Behaviour
{
public:
    MobSpawner();
    MobSpawner(unsigned int _id, std::string const& _name,
               EntityManager *manager);
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

public:
    static const RTypes::my_uint16_t Mask   = ComponentMask::MobSpawnerMask;

protected:
    ObjectPool<GameObject, Mob>  _mobs;
};

#endif /* !MOBSPAWNER_HPP_ */
