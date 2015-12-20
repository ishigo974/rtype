#include "Button.hpp"

Button::Button(gu::Rect<float> const& rect, std::string const& label, unsigned int size)
        : GUIElement(rect), _rect(sf::Vector2f(static_cast<float>(rect.w),
                                               static_cast<float>(rect.h))), _label(rect, label, size)
{
    this->_rect.setPosition(static_cast<float>(rect.x),
                            static_cast<float>(rect.y));
    this->_rect.setFillColor(sf::Color::Transparent);
    this->_rect.setOutlineColor(sf::Color::Red);
    this->_rect.setOutlineThickness(2.f);
}

Button::~Button()
{ }

void    Button::draw(sf::RenderWindow& win)
{
    win.draw(this->_rect);
    this->_label.draw(win);
}
