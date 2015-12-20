#ifndef GUIELEMENT_HPP_
# define GUIELEMENT_HPP_

# include <SFML/Graphics.hpp>
# include "Rect.hpp"

class	GUIElement
{
public:
  GUIElement(gu::Rect<int> const& rect);
  virtual ~GUIElement();

public:
  virtual void	draw(sf::RenderWindow&) = 0;
  bool		intersect(int x, int y);

protected:
  gu::Rect<int>	_rect;
};

#endif // !GUIELEMENT_HPP_
