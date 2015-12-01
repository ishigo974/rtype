#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <assert.h>
#include "GameObject.hpp"
#include "EntityManager.hpp"
#include "Renderer.hpp"
#include "SpriteRenderer.hpp"

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
	Transform tr(3, "yoy", cu::Position(100, 100), cu::Scale(1, 1), cu::Rotation(0));
	a->addComponent(sr);
	a->addComponent(tr);
	r.init();
	std::cout << "ok" << std::endl;
	r.draw(*a);
	std::cout << "ko" << std::endl;
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