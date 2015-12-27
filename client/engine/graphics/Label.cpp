#include "Label.hpp"

Label::Label(gu::Rect<float> const& rect, std::string const& str, unsigned int size,
	     std::string const& font) :
  GUIElement(rect), _size(size)
{
  this->_font.loadFromFile(font);
  this->_text.setFont(this->_font);
  this->_text.setString(str);
  this->_text.setCharacterSize(size);
  this->_text.setPosition(rect.x, rect.y);
}

Label::~Label()
{}

std::vector<const sf::Drawable *>    Label::getDrawable() const
{
    std::vector<const sf::Drawable *> obj(0);

    obj.push_back(static_cast<const sf::Drawable *>(&_text));
    return obj;
}
