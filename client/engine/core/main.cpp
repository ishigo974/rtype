#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.hpp"

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

void gameObjectTest()
{
}

int main()
{
    gameObjectTest();
    return 0;
}