//
// Created by fourdr_b on 24/12/15.
//

#include "NetPlayerObject.hpp"

NetPlayerObject::NetPlayerObject()
{ }

NetPlayerObject::NetPlayerObject(unsigned int id, std::string const& name, EntityManager *em)
        : GameObject(id, name, 1), _em(em)
{ }
