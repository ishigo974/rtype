//
// Created by fourdr_b on 24/12/15.
//

#include "NetPlayerObject.hpp"

NetPlayerObject::NetPlayerObject()
{ }

NetPlayerObject::NetPlayerObject(unsigned int id, std::string const& name, EntityManager *em)
        : GameObject(id, name, 0), _em(em)
{ }

NetPlayerObject::NetPlayerObject(NetPlayerObject& o) : GameObject(o)
{
    _em = o._em;
}

NetPlayerObject::NetPlayerObject(NetPlayerObject&& o) : NetPlayerObject(o)
{
    swap(o);
}

NetPlayerObject& NetPlayerObject::operator=(NetPlayerObject o)
{
    swap(o);

    return (*this);
}

NetPlayerObject::~NetPlayerObject()
{

}

void NetPlayerObject::swap(NetPlayerObject& o)
{
    using std::swap;

    swap(_em, o._em);
}

namespace std
{
    template<>
    void swap<NetPlayerObject>(NetPlayerObject& a, NetPlayerObject& b)
    {
        a.swap(b);
    }
}
