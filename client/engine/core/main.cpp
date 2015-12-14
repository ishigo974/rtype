#include <SFML/Graphics.hpp>
#include <assert.h>
#include "GameObject.hpp"
#include "StateMachine.hpp"
#include "CommandSystem.hpp"
#include "Event.hpp"
#include "EntityManager.hpp"
#include "Behaviour.hpp"
#include "Input.hpp"
#include "Event.hpp"
#include "Renderer.hpp"
#include "BigBen.hpp"
#include "ScrollingBackground.hpp"
#include "Mob.hpp"
#include "Player.hpp"

bool gameObjectTest(EntityManager & entityManager)
{
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
    Transform t   = a->transform();

    assert(be != nullptr);
    assert(be->getName() == "Behave");

    assert(t.getPosition().X() == 0);
    t.getPosition().setX(100);

    std::cout << a->toString();
    std::cout << b->toString();

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
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "i = " << i << " ; elapsed = "
            << BigBen::get().getElapsedtime() << std::endl;
        std::cout << "i = " << i << " ; fixedElapsed = "
            << BigBen::get().getFixedElapsedtime() << std::endl;
    }

    return (true);
}

void backgroundTest()
{
    Renderer r;
    Input i(r.getWindow());
    EntityManager entityManager;
    GameObject *a = entityManager.createEntity<GameObject>("Background", 1);
    cu::Event e;
    std::stringstream ss;
    CommandSystem	cmds(&entityManager);
    ss << "../res/bg" << rand() % 4 + 1 << ".jpg";

    GameObject *obj = entityManager.createEntity<GameObject>("Mob", 2);
    GameObject *p = entityManager.createEntity<GameObject>("Player", 3);

    entityManager.attachComponent<Transform>(a, cu::Position(0, 0));
    entityManager.attachComponent<SpriteRenderer>(a, "lel", ss.str(),
            gu::Rect<int>(0, 0, 1280, 720));
    entityManager.attachComponent<ScrollingBackground>(a, "lal", 60, a);

    entityManager.attachComponent<Transform>(obj, cu::Position(0, 0));
    entityManager.attachComponent<SpriteRenderer>(obj, "Mob", "../res/mob.gif", gu::Rect<int>(0, 0, 30, 30));
    entityManager.attachComponent<Mob>(obj, "Mob", 1, 2, obj);

    entityManager.attachComponent<Transform>(p, cu::Position(0, 0));
    Transform *t = p->getComponent<Transform>();
    t->getPosition().setX(600);
    t->getPosition().setY(680);
    entityManager.attachComponent<SpriteRenderer>(p, "Player", "../res/player.gif", gu::Rect<int>(0, 0, 30, 30));
    entityManager.attachComponent<Player>(p, "Player", 100, 2, p);


    r.init();
    e.key = cu::Event::LAST_ACTION;
    a->getComponent<ScrollingBackground>()->setEnabled(true);
    ScrollingBackground *bg = a->getComponent<ScrollingBackground>();

    obj->getComponent<Mob>()->setEnabled(true);
    Mob *mob = obj->getComponent<Mob>();

    p->getComponent<Player>()->setEnabled(true);
    Player *player = p->getComponent<Player>();


    while (e.key != cu::Event::ESCAPE)
    {
        while (i.pollEvent(e))
        {
            if (e.type == cu::Event::Closed)
            {
                std::cout << "Close button pressed" << std::endl;
                return ;
            }
            if (e.type == cu::Event::KeyPressed)
	      {
		cmds.addCommand(e);
                std::cout << "Key pressed : " << e.key << std::endl;
	      }
        }
        bg->update(BigBen::get().getElapsedtime());
	mob->update(BigBen::get().getElapsedtime());
        player->update(BigBen::get().getElapsedtime());
	r.draw(*a);
        r.draw(*obj);
        r.draw(*p);
        r.render();
    }
    std::cout << "Escape pressed" << std::endl;
}

bool stateMachineTest()
{
    State        ini("S0");
    cu::Position pos1, pos2;

    pos1 = cu::Position(5.0f, 5.0f);
    pos2 = cu::Position(5.0f, 5.0f);

    ini.addTransition("S2", [](cu::Position* a, cu::Position* b)
            {
            return (*a == *b);
            },
            &pos1, &pos2);

    StateMachine sm(0, ini);

    State s1("S1");
    State s2("S2");

    sm.addState(s1);
    sm.addState(s2);

    sm.move();

    assert(sm.getCurrent().getName() == s2.getName());

    return (true);
}

// bool commandSystemTest(EntityManager *entityManager)
// {
//     CommandSystem cmds(entityManager);
//     cu::Event upEvent;
//     cu::Event downEvent;

//     upEvent.key = cu::Event::UP;
//     downEvent.key = cu::Event::DOWN;

//     cmds.addCommand(upEvent);
//     cmds.addCommand(downEvent);
//     std::cout << cmds.toString() << std::endl;
//     assert(cmds.getSize() == 2);
//     cmds.process();
//     return (true);
// }

bool	mobTest()
{
  EntityManager entityManager;
  GameObject *obj = entityManager.createEntity<GameObject>("Test", 1);

  entityManager.attachComponent<Transform>(obj, cu::Position(0, 0));
  entityManager.attachComponent<Mob>(obj, "Mob", 1, 2, obj);
  entityManager.attachComponent<SpriteRenderer>(obj, "Mob", "../res/r-typesheet19.gif", gu::Rect<int>(100, 0, 100, 300));
  obj->getComponent<Mob>()->setEnabled(true);
  Mob *mob = obj->getComponent<Mob>();
  std::cout << mob->getName() << std::endl;
  mob->update(BigBen::get().getElapsedtime());
  // assert(obj->getComponent<Transform>()->getPosition().Y() == 200);
  return (true);
}

void menuTest()
{
    Renderer r;
    Input i(r.getWindow());
    EntityManager entityManager;
    cu::Event e;

    GameObject *menu = entityManager.createEntity<GameObject>("menu", 1);

    std::stringstream ss;
    ss << "../res/menu" << rand() % 4 + 1 << ".jpg";

    entityManager.attachComponent<Transform>(menu, cu::Position(0, 0));
    entityManager.attachComponent<SpriteRenderer>(menu, "sr", ss.str(),
						  gu::Rect<int>(0, 0, 1280, 720));
    entityManager.attachComponent<ScrollingBackground>(menu, "sb", 0, menu);

    State initialState("Aeris");
    State mainMenu("Main Menu");

    initialState.addTransition("MainMenu", [](cu::Event const* e)
            {
	      return e->type == cu::Event::KeyReleased;
            },
            &e);

    entityManager.attachComponent<StateMachine>(menu, initialState);

    r.init();
    e.type = cu::Event::None;
    e.key = cu::Event::LAST_ACTION;
    menu->getComponent<ScrollingBackground>()->setEnabled(true);
    ScrollingBackground *bg = menu->getComponent<ScrollingBackground>();
    StateMachine *sm = menu->getComponent<StateMachine>();
    sm->addState(mainMenu);
    std::cout << "Current : " << sm->getCurrent().getName() << std::endl;

    while (e.key != cu::Event::ESCAPE)
    {
        while (i.pollEvent(e))
        {
            if (e.type == cu::Event::Closed)
            {
                std::cout << "Close button pressed" << std::endl;
                return ;
            }
            if (e.type == cu::Event::KeyPressed)
                std::cout << "Key pressed : " << e.key << std::endl;
            if (e.type == cu::Event::KeyReleased)
                std::cout << "Key released : " << e.key << std::endl;
	    sm->move();
        }
        bg->update(BigBen::get().getElapsedtime());
	std::cout << "Current : " << sm->getCurrent().getName() << std::endl;
        r.draw(*menu);
        r.render();
    }
    std::cout << "Escape pressed" << std::endl;
}

int main()
{
  EntityManager entityManager;

  srand(static_cast<unsigned>(time(nullptr)));
  if (gameObjectTest(entityManager))
    std::cout << "\e[32mgameObjectTest passed -> OK\e[0m" << std::endl << std::endl;
  if (timeTest())
    std::cout << "\e[32mtimeTest passed -> OK\e[0m" << std::endl << std::endl;
  if (stateMachineTest())
    std::cout << "\e[32mstateMachineTest passed -> OK\e[0m" << std::endl << std::endl;
  // if (commandSystemTest(&entityManager))
  //   std::cout << "\e[32mCommandSystem passed -> OK\e[0m" << std::endl;

  // backgroundTest();
  menuTest();

  return 0;
}
