#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <assert.h>
#include "GameObject.hpp"
#include "EntityManager.hpp"
#include "Behaviour.hpp"

bool gameObjectTest()
{
    EntityManager entityManager;

    GameObject *a = entityManager.createEntity<GameObject>("Test", 1);
    assert(a->getId() == 1);
    assert(a->getName() == "Test");
    assert(a->getLayer() == 1);

    GameObject *b = entityManager.createEntity<GameObject>("Test", 2);
    assert(b->getId() == 2);
    assert(b->getName() == "Test");
    assert(b->getLayer() == 2);

    a->addComponent(std::make_unique<Behaviour>(10, "Behave"));

    Behaviour *be = a->getComponent<Behaviour>();

    assert(be != nullptr);
    assert(be->getName() == "Behave");

    std::cout << a->toString() << std::endl;
    std::cout << b->toString() << std::endl;

    return (true);
}

int main()
{
    if (gameObjectTest())
        std::cout << "gameObjectTest passed -> OK" << std::endl;

    return (0);
}