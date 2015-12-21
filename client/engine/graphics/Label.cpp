#include "Label.hpp"

Label::Label(gu::Rect<float> const& rect, std::string const& str, unsigned int size,
	     std::string const& font) :
  GUIElement(rect), _size(size)
{
  this->_font.loadFromFile(font);
  this->_text.setFont(this->_font);
  this->_text.setString(str);
  this->_text.setCharacterSize(size);
  this->_text.setPosition(static_cast<float>(rect.x),
			  static_cast<float>(rect.y));
  static_cast<void>(_size); //TODO LE VIRER
}

Label::~Label()
{}

void	Label::draw(sf::RenderWindow& win)
{
  win.draw(this->_text);
}
