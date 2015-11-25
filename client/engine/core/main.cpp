#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include <memory>
#include "GameObject.hpp"
#include "Component.hpp"

void sfml_test()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape  shape(100.f);

    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

bool gameObjectTest()
{
    Component c(1, "Test", 1);
    Component d(c);

    std::cout << d.toString() << std::endl;

    return (true);
}

int main()
{
    assert(gameObjectTest());

    return 0;
}