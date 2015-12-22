#ifndef BUTTON_HPP_
# define BUTTON_HPP_

# include <string>
# include <vector>
# include "GUIElement.hpp"
# include "Label.hpp"

class Button : public GUIElement
{
public:
    Button(gu::Rect<float> const& rect,
           std::string const& label,
           unsigned int size);
    virtual ~Button();

public:
    virtual std::vector<const sf::Drawable *>    getDrawable() const;

private:
    sf::RectangleShape _rect;
    Label              _label;
};

#endif // !BUTTON_HPP_
