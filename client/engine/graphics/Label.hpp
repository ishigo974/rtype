#ifndef LABEL_HPP_
# define LABEL_HPP_

# include <string>
# include <SFML/Graphics.hpp>
# include "GUIElement.hpp"

class Label : public GUIElement
{
public:
  Label(gu::Rect<int> const& rect, std::string const& str, unsigned int size,
	std::string const& font = "../res/cs_regular.ttf");
  virtual ~Label();

public:
  virtual void	draw(sf::RenderWindow&);

private:
  unsigned int	_size;
  sf::Font	_font;
  sf::Text	_text;
};

#endif // !LABEL_HPP_
