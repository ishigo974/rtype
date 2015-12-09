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
#include "SoundEffect.hpp"
#include "SoundEffectPlayer.hpp"
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

int SoundEffectPlayerTest()
{
	EntityManager entityManager;
	SoundEffectPlayer soundPlayer;
	GameObject *gameObj = entityManager.createEntity<GameObject>("Test", 1);
	SoundEffect *sEffect;

	entityManager.attachComponent<SoundEffect>(gameObj, "testLaser", "res/laser1.wav");

	soundPlayer.play(*gameObj);

	sEffect = gameObj->getComponent<SoundEffect>();
	while (sEffect->isPlaying())
	{
		std::cout << "Playing sound..." << std::endl;
		std::cout << (sEffect->isPlaying() ? "true" : "false") << std::endl;
		sf::sleep(sf::milliseconds(500));
	}
	return 0;
}

int main()
{
	//if (gameObjectTest())
	//	std::cout << "gameObjectTest passed -> OK" << std::endl;
	//if (timeTest())
	//	std::cout << "timeTest passed -> OK" << std::endl;
	//inputTest();
	//renderTest();
	SoundEffectPlayerTest();
	return (0);
}
