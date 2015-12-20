#include "Label.hpp"

Label::Label(gu::Rect<int> const& rect, std::string const& str, unsigned int size,
	     std::string const& font) :
  GUIElement(rect), _size(size)
{
  this->_font.loadFromFile(font);
  this->_text.setFont(this->_font);
  this->_text.setString(str);
  this->_text.setCharacterSize(size);
  this->_text.setPosition(static_cast<float>(rect.x),
			  static_cast<float>(rect.y));
}

Label::~Label()
{}

void	Label::draw(sf::RenderWindow& win)
{
  win.draw(this->_text);
}
