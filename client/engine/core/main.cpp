#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <assert.h>
//#include <unistd.h> // Windows les gars.......................................................................................................................
#include "GameObject.hpp"
#include "EntityManager.hpp"
#include "Renderer.hpp"
#include "SpriteRenderer.hpp"
#include "Behaviour.hpp"
#include "Input.hpp"
#include "Event.hpp"
#include "BigBen.hpp"
#include "ScrollingBackground.hpp"

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

    entityManager.attachComponent<Behaviour>(a, "Behave");

    Behaviour *be = a->getComponent<Behaviour>();
    Transform t = a->transform();

    assert(be != nullptr);
    assert(be->getName() == "Behave");

    assert(t.getPosition().X() == 0);
    t.getPosition().setX(100);

    std::cout << a->toString() << std::endl;
    std::cout << b->toString() << std::endl;

    return (true);
}

void renderAndInputsTest()
{
  Renderer r;
  Input i(r.getWindow());
  EntityManager entityManager;
  GameObject *a = entityManager.createEntity<GameObject>("Test", 1);
  cu::Event e;

  entityManager.attachComponent<Transform>(a, cu::Position(100, 100));
  entityManager.attachComponent<SpriteRenderer>(a, "lel", "../res/r-typesheet1.gif", gu::Rect<int>(100, 0, 100, 300));

  r.init();
  e.key = cu::Event::LAST_ACTION;

  while (e.key != cu::Event::ESCAPE)
    {
      while (i.pollEvent(e))
	{
	  std::cout << "Key pressed : " << e.key << std::endl;
	}
      r.draw(*a);
      r.render();
    }
  std::cout << "Escape pressed" << std::endl;
}

bool timeTest()
{
    for (int i = 0 ; i < 5 ; ++i)
    {
        std::cout << "i = " << i << " ; elapsed = "
		  << BigBen::get().getElapsedtime() << std::endl;
        std::cout << "i = " << i << " ; fixedElapsed = "
		  << BigBen::get().getFixedElapsedtime() << std::endl;
        //usleep(5000); // Windows...
    }

    return (true);
}

void backgroundTest()
{
  Renderer r;
  Input i(r.getWindow());
  EntityManager entityManager;
  GameObject *a = entityManager.createEntity<GameObject>("Test", 1);
  cu::Event e;

  entityManager.attachComponent<Transform>(a, cu::Position(0, 0));
  entityManager.attachComponent<SpriteRenderer>(a, "lel", "../res/bg1.jpg",
						gu::Rect<int>(0, 0, 1280, 720));
  entityManager.attachComponent<ScrollingBackground>(a, "lal", 50, a);

  r.init();
  e.key = cu::Event::LAST_ACTION;

  while (e.key != cu::Event::ESCAPE)
    {
      while (i.pollEvent(e))
	{
	  std::cout << "Key pressed : " << e.key << std::endl;
	}
      a->getComponent<ScrollingBackground>()->setEnabled(true);
      a->getComponent<ScrollingBackground>()->update(BigBen::get().getElapsedtime());
      r.draw(*a);
      r.render();
    }
  std::cout << "Escape pressed" << std::endl;
}

int main()
{
  if (gameObjectTest())
    std::cout << "gameObjectTest passed -> OK" << std::endl;
  if (timeTest())
    std::cout << "timeTest passed -> OK" << std::endl;
  // renderAndInputsTest();
  backgroundTest();
  return (0);
}
