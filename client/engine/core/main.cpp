#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <assert.h>
#include "GameObject.hpp"
#include "EntityManager.hpp"

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
    EntityManager entityManager;

    GameObject *a = entityManager.createEntity<GameObject>("Test", 1);
    assert(a->getId() == 1);
    assert(a->getName() == "Test");
    assert(a->getLayer()== 1);

    GameObject *b = entityManager.createEntity<GameObject>("Test", 2);
    assert(b->getId() == 2);
    assert(b->getName() == "Test");
    assert(b->getLayer()== 2);

    std::cout << a->toString() << std::endl;
    std::cout << b->toString() << std::endl;

    return (true);
}

int main()
{
    if (gameObjectTest())
        std::cout << "gameObjectTest passed -> OK" << std::endl;

    return 0;
}