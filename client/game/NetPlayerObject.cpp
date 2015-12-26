//
// Created by fourdr_b on 24/12/15.
//

#include <UDPView.hpp>
#include "NetPlayerObject.hpp"
#include "NetPlayerComp.hpp"

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

void NetPlayerObject::init()
{
    _em->attachComponent<SpriteRenderer>(this, "NetPlayerSprite", "player", gu::Rect<int>(67, 3, 32, 12));
    _em->attachComponent<UDPView>(this, "NetPlayerUDPView");
    _em->attachComponent<NetPlayerComp>(this, "NPC", _em, 10, 5);
    getComponent<NetPlayerComp>()->init();
}
