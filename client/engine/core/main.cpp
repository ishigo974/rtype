#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <assert.h>
#include "GameObject.hpp"
#include "EntityManager.hpp"
#include "Renderer.hpp"

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

void renderTest()
{
	EntityManager entityManager;
	Renderer r;
	GameObject *a = entityManager.createEntity<GameObject>("Test", 1);
	SpriteRenderer sr(2, "lel", "../res/r-typesheet1.gif", gu::Rect<int>(100, 0, 100, 100));
	a->addComponent(sr);
	r.draw(*a);
	while (1)
	{
		r.render();
	}
}

int main()
{
//    if (gameObjectTest())
//        std::cout << "gameObjectTest passed -> OK" << std::endl;
	renderTest();
    return (0);
}