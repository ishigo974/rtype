#ifndef RENDERER_HPP_
# define RENDERER_HPP_

# include <SFML/Graphics.hpp>
# include "Resources.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer() {}
	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;

public:
	void		init();

private:
	sf::RenderWindow	_win;
	Resources			_res;
};

#endif // !RENDERER_HPP_