#ifndef RENDERER_HPP_
# define RENDERER_HPP_

# include <SFML/Graphics.hpp>
# include "Resources.hpp"
# include "GameObject.hpp"

class Renderer
{
public:
    static unsigned int const width;
    static unsigned int const height;

public:
    Renderer();
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
public:
    void init();
    void render();

public:
	sf::RenderWindow& getWindow();

public:
    // It souldn't stay public, really
    void draw(const GameObject&);

private:
    sf::RenderWindow _win;
    Resources        _res;
};

#endif // !RENDERER_HPP_
