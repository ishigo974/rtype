#ifndef RENDERER_HPP_
# define RENDERER_HPP_

# include "Resources.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer() {}
	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;

private:
	Resources	_res;
};

#endif // !RENDERER_HPP_