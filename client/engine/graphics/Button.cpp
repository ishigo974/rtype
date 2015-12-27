#include "Button.hpp"

Button::Button(gu::Rect<float> const& rect, std::string const& label, unsigned int size)
        : GUIElement(rect), _rect(sf::Vector2f(static_cast<float>(rect.w),
                                               static_cast<float>(rect.h))), _label(rect, label, size)
{
    this->_rect.setPosition(rect.x, rect.y);
    this->_rect.setFillColor(sf::Color::Transparent);
    this->_rect.setOutlineColor(sf::Color::Red);
    this->_rect.setOutlineThickness(2.f);
}

Button::~Button()
{ }

std::vector<const sf::Drawable *>    Button::getDrawable() const
{
    std::vector<const sf::Drawable *> obj(0);

    obj.push_back(static_cast<const sf::Drawable *>(&_rect));
    obj.push_back(_label.getDrawable()[0]);
    return obj;
}
