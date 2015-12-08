#include <SFML/Graphics.hpp>
#include <assert.h>
#include "GameObject.hpp"
#include "StateMachine.hpp"
#include "CommandSystem.hpp"
#include "Event.hpp"

//bool gameObjectTest()
//{
//    EntityManager entityManager;
//
//    GameObject *a = entityManager.createEntity<GameObject>("Test", 1);
//    assert(a->getId() == 1);
//    assert(a->getName() == "Test");
//    assert(a->getLayer() == 1);
//
//    GameObject *b = entityManager.createEntity<GameObject>("Test", 2);
//    assert(b->getId() == 2);
//    assert(b->getName() == "Test");
//    assert(b->getLayer() == 2);
//
//    entityManager.attachComponent<Behaviour>(a, "Behave");
//
//    Behaviour *be = a->getComponent<Behaviour>();
//    Transform t   = a->transform();
//
//    assert(be != nullptr);
//    assert(be->getName() == "Behave");
//
//    assert(t.getPosition().X() == 0);
//    t.getPosition().setX(100);
//
//    std::cout << a->toString() << std::endl;
//    std::cout << b->toString() << std::endl;
//
//    return (true);
//}
//
//void renderTest()
//{
//    EntityManager entityManager;
//    Renderer      r;
//    GameObject    *a = entityManager.createEntity<GameObject>("Test", 1);
//
//    entityManager.attachComponent<Transform>(a, cu::Position(100, 100));
//    entityManager.attachComponent<SpriteRenderer>(a, "lel", "r-typesheet1.gif", gu::Rect<int>(100, 0, 100, 300));
//
//    r.init();
//
//    while (1)
//    {
//        usleep(10000);
//        r.draw(*a);
//        r.render();
//    }
//}
//
//bool timeTest()
//{
//    for (int i = 0; i < 5; ++i)
//    {
//        std::cout << "i = " << i << " ; elapsed = " << BigBen::get().getElapsedtime() << std::endl;
//        std::cout << "i = " << i << " ; fixedElapsed = " << BigBen::get().getFixedElapsedtime() << std::endl;
//        usleep(5000);
//    }
//
//    return (true);
//}

bool stateMachineTest()
{
    State        ini("S0");
    cu::Position pos1, pos2;

    pos1 = cu::Position(5.0f, 5.0f);
    pos2 = cu::Position(5.0f, 5.0f);

    ini.addTransition("S2", [](cu::Position&& a, cu::Position&& b)
                      {
                          return (a == b);
                      },
                      pos1, pos2);

    StateMachine sm(ini);

    State s1("S1");
    State s2("S2");

    sm.addState(s1);
    sm.addState(s2);

    sm.move();

    assert(sm.getCurrent().getName() == s2.getName());

    return (true);
}

bool commandSystemTest()
{
  CommandSystem cmds;
  cu::Event upEvent;
  cu::Event downEvent;

  upEvent.key = cu::Event::UP;
  downEvent.key = cu::Event::DOWN;

  cmds.addCommand(upEvent);
  cmds.addCommand(downEvent);
  std::cout << cmds.toString() << std::endl;
  assert(cmds.getSize() == 2);
  return (true);
}

int main()
{
//    if (gameObjectTest())
//        std::cout << "gameObjectTest passed -> OK" << std::endl;
//    if (timeTest())
//        std::cout << "timeTest passed -> OK" << std::endl;
//    renderTest();
    stateMachineTest();
    commandSystemTest();
    return (0);
}
