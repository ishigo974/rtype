#ifndef RENDERER_HPP_
# define RENDERER_HPP_

# include <SFML/Graphics.hpp>
# include "Resources.hpp"
# include "GameObject.hpp"

class Renderer
{
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
    // To be honest, I don't know yet if it will stay public
    void draw(const GameObject&);

private:
    sf::RenderWindow _win;
    Resources        _res;
};

#endif // !RENDERER_HPP_