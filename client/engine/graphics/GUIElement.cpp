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

