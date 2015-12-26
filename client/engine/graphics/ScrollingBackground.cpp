#include "ScrollingBackground.hpp"
#include "GameObject.hpp"
#include "SpriteRenderer.hpp"

ScrollingBackground::ScrollingBackground()
{}

ScrollingBackground::ScrollingBackground(unsigned int _id,
					 std::string const& _name,
					 double speed) :
  Behaviour(_id, _name), _speed(speed)
{
	_enabled = true;
}

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
    inline void swap<ScrollingBackground>(ScrollingBackground& a, ScrollingBackground& b)
    {
        a.swap(b);
    }
}

void ScrollingBackground::update(double elapsedTime)
{
	SpriteRenderer *sr = static_cast<GameObject *>(parent())->getComponent<SpriteRenderer>();
	if (sr == nullptr)
		return;

	auto rect = sr->getRect();
	rect.x += static_cast<int>(this->_speed * elapsedTime);
	sr->setRect(rect);
}
