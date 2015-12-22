#ifndef GUIELEMENT_HPP_
# define GUIELEMENT_HPP_

# include <SFML/Graphics.hpp>
# include "Rect.hpp"

class GUIElement
{
public:
    GUIElement();
    GUIElement(gu::Rect<float> const& rect);
    GUIElement(GUIElement const& other);
    GUIElement(GUIElement&& other);
    virtual ~GUIElement();

    void swap(GUIElement& other);

public:
    virtual std::vector<const sf::Drawable *> getDrawable() const = 0;
    bool                                      intersect(int x, int y);

protected:
    gu::Rect<float> _rect;
};

#endif // !GUIELEMENT_HPP_
