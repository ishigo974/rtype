#include "GUIElement.hpp"

GUIElement::GUIElement(gu::Rect<float> const& rect) :
  _rect(rect)
{}

GUIElement::~GUIElement()
{}

bool	GUIElement::intersect(int x, int y)
{
  return (x >= _rect.x && x <= _rect.x + _rect.w
	  && y >= _rect.y && y <= _rect.y + _rect.h);
}

GUIElement::GUIElement(GUIElement const& other):
    _rect(other._rect)
{

}

GUIElement::GUIElement(GUIElement&& other) : GUIElement(other)
{
    swap(other);
}

GUIElement& GUIElement::operator=(GUIElement other)
{
    swap(other);

    return (*this);
}

void GUIElement::swap(GUIElement& other)
{
    using std::swap;

    swap(_rect, other._rect);
}

namespace std
{
    template<>
    void swap<GUIElement>(GUIElement& a, GUIElement& b)
    {
        a.swap(b);
    }
}

void GUIElement::draw(sf::RenderWindow &)
{ }

GUIElement::GUIElement()
{ }
