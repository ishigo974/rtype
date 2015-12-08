#include "ScrollingBackground.hpp"
#include "GameObject.hpp"
#include "SpriteRenderer.hpp"

ScrollingBackground::ScrollingBackground()
{}

ScrollingBackground::ScrollingBackground(unsigned int _id,
					 std::string const& _name,
					 unsigned int speed,
					 Object *parent) :
  Behaviour(_id, _name, parent), _speed(speed)
{}

ScrollingBackground::ScrollingBackground(ScrollingBackground const& other) :
  Behaviour(other)
{
  _enabled = other.isEnabled();
}

ScrollingBackground::ScrollingBackground(ScrollingBackground&& other) :
  ScrollingBackground(other)
{
  swap(other);
}

ScrollingBackground& ScrollingBackground::operator=(ScrollingBackground other)
{
  swap(other);

  return (*this);
}

ScrollingBackground::~ScrollingBackground()
{}

bool ScrollingBackground::operator==(ScrollingBackground const& other)
{
  return (Behaviour::operator==(other));
}

bool ScrollingBackground::operator!=(ScrollingBackground const& other)
{
  return (!ScrollingBackground::operator==(other));
}

void ScrollingBackground::swap(ScrollingBackground& other)
{
  using std::swap;

  swap(_enabled, other._enabled);
}

namespace std
{
template<>
void swap<ScrollingBackground>(ScrollingBackground& a, ScrollingBackground& b)
{
  a.swap(b);
}
}

void ScrollingBackground::update(double elapsedTime)
{
  if (!_enabled)
    return ;

  SpriteRenderer *sr = static_cast<GameObject *>(this->_parent)
    ->getComponent<SpriteRenderer>(); // !

  auto rect = sr->getRect();
  rect.x += this->_speed * elapsedTime;
  // if (rect.x > rect.w)
  //   rect.x = 0;
  sr->setRect(rect);
}
