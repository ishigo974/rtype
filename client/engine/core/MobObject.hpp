#ifndef MOBOBJECT_HPP_
# define MOBOBJECT_HPP_

# include "GameObject.hpp"
# include "EntityManager.hpp"

class MobObject : public GameObject
{
public:
    MobObject();
    MobObject(unsigned int _id, std::string const& _name, int _layer, EntityManager *manager = nullptr);
    virtual ~MobObject();

    MobObject(MobObject const& other);
    MobObject(MobObject&& other);
    MobObject& operator=(MobObject other);

    virtual bool operator==(MobObject const& other);
    virtual bool operator!=(MobObject const& other);

    std::string toString() const;

    void init();
    void deleteObject();
    void swap(MobObject& other);
    void reset();


private:
    EntityManager *_entityManager;
};

#endif /* !MOBOBJECT_HPP_ */
