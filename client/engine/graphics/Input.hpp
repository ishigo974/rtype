#ifndef		INPUT_HPP_
# define	INPUT_HPP_

# include <vector>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "Event.hpp"

class Input
{
public:
  Input(sf::RenderWindow&);
  ~Input();

  Input() = delete;
  Input(Input const&) = delete;
  Input& operator=(Input const&) = delete;

public:
  bool	pollEvent(cu::Event &);
  bool	isKeyPressed(cu::Event::KeyEvent);

private:
  bool	key(sf::Event const&, cu::Event&);
  bool	mouse(sf::Event const&, cu::Event&);

private:
  sf::RenderWindow&				_win;
  std::vector<sf::Keyboard::Key>	_bindings;
};

#endif		// !INPUT_HPP_
