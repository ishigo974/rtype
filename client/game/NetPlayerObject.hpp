#ifndef RTYPE_NETPLAYEROBJECT_HPP
# define RTYPE_NETPLAYEROBJECT_HPP

# include <EntityManager.hpp>
# include "GameObject.hpp"

class NetPlayerObject : public GameObject
{
public:
    NetPlayerObject();
    NetPlayerObject(unsigned int id, std::string const& name, EntityManager *em,
                    unsigned int playerId);
    NetPlayerObject(NetPlayerObject& o);
    NetPlayerObject(NetPlayerObject&& o);
    NetPlayerObject& operator=(NetPlayerObject o);

    virtual ~NetPlayerObject();

    void swap(NetPlayerObject& o);

public:
    void init();
    unsigned int getPlayerId() const;

private:
    EntityManager*  _em;
    unsigned int    _playerId;
};

#endif //RTYPE_NETPLAYEROBJECT_HPP
