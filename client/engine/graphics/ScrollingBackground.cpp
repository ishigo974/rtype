#include "ScrollingBackground.hpp"
#include "GameObject.hpp"
#include "SpriteRenderer.hpp"

ScrollingBackground::ScrollingBackground()
{}

ScrollingBackground::ScrollingBackground(unsigned int _id,
					 std::string const& _name,
					 double speed,
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
  static double deltaPix = 0;
  if (!_enabled)
    return ;

  SpriteRenderer *sr = static_cast<GameObject *>(this->_parent)
    ->getComponent<SpriteRenderer>();
  if (sr == nullptr)
    return;

  auto rect = sr->getRect();
  deltaPix += this->_speed * elapsedTime;
  if (deltaPix >= 1)
  {
    rect.x += static_cast<int>(deltaPix);
    deltaPix = 0;
  }
  sr->setRect(rect);
}
