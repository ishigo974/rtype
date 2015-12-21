#include <chrono>
#include "Collider.hpp"
#include "GameObject.hpp"
#include "EntityManager.hpp"

Collider::Collider() : Component()
{ }

Collider::Collider(unsigned int _id, std::string const& _name, int width, int height)
  : Component(_id, _name), _bounds(0, 0, width, height)
{ }

Collider::Collider(Collider const& other) : Component(other)
{
    _bounds = other._bounds;
}

Collider::Collider(Collider&& other) : Collider(other)
{
    swap(other);
}

Collider& Collider::operator=(Collider other)
{
    swap(other);

    return (*this);
}

Collider::~Collider()
{ }

bool Collider::operator==(Collider const& other)
{
    return (Component::operator==(other) &&
            _bounds == other._bounds);
}

bool Collider::operator!=(Collider const& other)
{
    return Component::operator!=(other);
}

void Collider::swap(Collider& other)
{
    using std::swap;

    swap(_bounds, other._bounds);
}

RTypes::my_uint16_t Collider::getMask() const
{
    return (Mask);
}

std::string Collider::toString() const
{
    //TODO : _bounds.toString()
    std::stringstream ss;

    ss << "Collider {"
    << "\n\tid: " << _id
    << "\n\tname: " << _name
    << "\n\tmask: " << Mask
    << "\n}" << std::endl;

    return (ss.str());
}

void Collider::fixedUpdate(double)
{
    auto tmp = EntityManager::getByMask(ComponentMask::ColliderMask);

    _bounds.x = static_cast<GameObject *>(this->parent())->transform().getPosition().X();
    _bounds.y = static_cast<GameObject *>(this->parent())->transform().getPosition().Y();
    //std::cout << static_cast<GameObject *>(this->parent())->transform().toString() << std::endl;
    for (auto e : tmp)
      {
      if (this->_bounds.intersects(static_cast<GameObject *>(e)->getComponent<Collider>()->_bounds))
        {
	  std::cout << "FIRST" << std::endl;
	  std::cout << "x == " << _bounds.x << std::endl;
	  std::cout << "y == " << _bounds.y << std::endl;
	  std::cout << "w == " << _bounds.w << std::endl;
	  std::cout << "h == " << _bounds.h << std::endl;

	  std::cout << "OTHER" << std::endl;
	  std::cout << "x == " << static_cast<GameObject *>(e)->getComponent<Collider>()->_bounds.x << std::endl;
	  std::cout << "y == " << static_cast<GameObject *>(e)->getComponent<Collider>()->_bounds.y << std::endl;
	  std::cout << "w == " << static_cast<GameObject *>(e)->getComponent<Collider>()->_bounds.w << std::endl;
	  std::cout << "h == " << static_cast<GameObject *>(e)->getComponent<Collider>()->_bounds.h << std::endl;
	  // std::cout << "Collision" << std::endl;
	  sendMessage(static_cast<Collider *>(e));
        }
    }
}

namespace std
{
    template<>
    inline void swap<Collider>(Collider& a, Collider& b)
    {
        a.swap(b);
    }
}

void Collider::sendMessage(Collider *e)
{
    static_cast<GameObject *>(parent())->sendMessage(*this, *e);
}
