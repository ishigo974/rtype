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
#include "Sound.hpp"
#include "Music.hpp"

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

void renderTest()
{
	EntityManager entityManager;
	Renderer r;
	GameObject *a = entityManager.createEntity<GameObject>("Test", 1);

    entityManager.attachComponent<Transform>(a, cu::Position(100, 100));
    entityManager.attachComponent<SpriteRenderer>(a, "lel", "r-typesheet1.gif", gu::Rect<int>(100, 0, 100, 300));

	r.init();

	while (1)
	{
        //usleep(10000); // Windows.......
		r.draw(*a);
		r.render();
	}
}

void inputTest()
{
  Renderer r;
  Input i(r.getWindow());
  cu::Event e;

  e.key = cu::Event::LAST_ACTION;
  while (e.key != cu::Event::ESCAPE)
    {
      while (i.pollEvent(e))
	{
	  std::cout << "Key pressed : " << e.key << std::endl;
	}
      r.render();
    }
}

bool timeTest()
{
    for (int i = 0 ; i < 5 ; ++i)
    {
        std::cout << "i = " << i << " ; elapsed = " << BigBen::get().getElapsedtime() << std::endl;
        std::cout << "i = " << i << " ; fixedElapsed = " << BigBen::get().getFixedElapsedtime() << std::endl;
        //usleep(5000); // Windows...
    }

    return (true);
}

int soundTest()
{
	Sound	s;
	Sound	s1;
	Sound	s2;

	Music	m;
	if (!m.setSound("res/music.wav"))
	{
		std::cout << "Cant load file music.wav: KO" << std::endl;
		return 1;
	}
	std::cout << "Start to play music..." << std::endl;
	m.play();

	sf::sleep(sf::milliseconds(1000));
	if (!s.setSound("res/laser1.wav"))
	{
		std::cout << "Cant load file laser1.wav: KO"<< std::endl;
		return 1;
	}
	std::cout << "Playing laser1.wav..." << std::endl;
	s.play();
	while (s.isPlaying())
		sf::sleep(sf::milliseconds(100));

	if (!s.setSound("res/laser2.wav"))
	{
		std::cout << "Cant load file laser2.wav: KO" << std::endl;
		return 1;
	}
	std::cout << "Playing laser2.wav..." << std::endl;
	s.play();
	while (s.isPlaying())
		sf::sleep(sf::milliseconds(100));

	std::cout << "Simultaneous sound..." << std::endl;
	s1.setSound("res/laser1.wav");
	s2.setSound("res/laser2.wav");

	s1.play();
	s2.play();

	std::cout << "Sound Effect tests: OK" << std::endl;

	//m.stop();
	std::cout << "Wait until music stop..."<< std::endl;
	while (m.isPlaying())
		sf::sleep(sf::milliseconds(100));
	std::cout << "Music tests: OK" << std::endl;

	return 0;
}

int main()
{
  //if (gameObjectTest())
  //  std::cout << "gameObjectTest passed -> OK" << std::endl;
  //if (timeTest())
  //  std::cout << "timeTest passed -> OK" << std::endl;
  //inputTest();
  // renderTest();
	soundTest();
	return (0);
}
