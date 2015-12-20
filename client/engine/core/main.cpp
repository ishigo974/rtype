#include <SFML/Graphics.hpp>
#include <assert.h>
#include "GameObject.hpp"
#include "StateMachine.hpp"
//#include "CommandSystem.hpp"
#include "Event.hpp"
#include "EntityManager.hpp"
#include "Behaviour.hpp"
#include "Input.hpp"
#include "Event.hpp"
#include "Renderer.hpp"
#include "BigBen.hpp"
#include "ScrollingBackground.hpp"
//#include "Mob.hpp"
//#include "Player.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "TextField.hpp"
//#include "Bullet.hpp"
#include "GUIManager.hpp"
#include "Menu.hpp"
//#include "ZobPool.hpp"
//#include "RCSVParser.hpp"

//bool gameObjectTest(EntityManager& entityManager)
//{
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
//    std::cout << a->toString();
//    std::cout << b->toString();
//
//    return (true);
//}
//
//bool timeTest()
//{
//    for (int i = 0; i < 5; ++i)
//    {
//        std::cout << "i = " << i << " ; elapsed = "
//        << BigBen::get().getElapsedtime() << std::endl;
//        std::cout << "i = " << i << " ; fixedElapsed = "
//        << BigBen::get().getFixedElapsedtime() << std::endl;
//    }
//
//    return (true);
//}
//
//void backgroundTest()
//{
//    Renderer          r;
//    Input             i(r.getWindow());
//    EntityManager     entityManager;
//    GameObject        *a = entityManager.createEntity<GameObject>("Background", 1);
//    cu::Event         e;
//    std::stringstream ss;
//    CommandSystem     cmds(&entityManager, &i);
//    ss << "bg" << rand() % 4 + 1;
//
//    GameObject *p   = entityManager.createEntity<GameObject>("Player", 3);
//    GameObject *bulletobj   = entityManager.createEntity<GameObject>("Bulletobj", 4);
//    // ObjectPool<Bullet> *bulletpool   = entityManager.createEntity<ObjectPool<Bullet> >("Bulletpool");
//    // (void)bulletpool;
//
//    std::vector<GameObject *>	objs;
//    std::vector<Mob *>	mobs;
//    objs.push_back(entityManager.createEntity<GameObject>("Mob", 2));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 5));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 6));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob4", 7));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob", 2));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 5));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 6));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 5));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 6));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob4", 7));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob", 2));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 5));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 6));
//    objs.push_back(entityManager.createEntity<GameObject>("Mob4", 7));
//
//    entityManager.attachComponent<SpriteRenderer>(a, "lel", ss.str(), gu::Rect<int>(0, 0, 1280, 720));
//    entityManager.attachComponent<ScrollingBackground>(a, "lal", 60);
//
//    int j = 0;
//    for (auto obj : objs)
//      {
//	entityManager.attachComponent<SpriteRenderer>(obj, "Mob", "mob", gu::Rect<int>(1, 4, 32, 21));
//	entityManager.attachComponent<Mob>(obj, "Mob", 1, 2, j % 4);
//        Transform *t = obj->getComponent<Transform>();
//	t->getPosition().setX(Renderer::width - 32);
//	switch (j)
//	  {
//	  case 0:
//	    t->getPosition().setX(rand() % (Renderer::width - 32));
//	    t->getPosition().setY(rand() % (Renderer::height - 21));
//	    break;
//	  case 1:
//	    t->getPosition().setY(rand() % (Renderer::height - 21));
//	    break;
//	  case 2:
//	    t->getPosition().setY(rand() % (Renderer::height - 21));
//	    break;
//	  case 3:
//	    t->getPosition().setY(rand() % (Renderer::height - 21));
//	    break;
//	  default:
//	    break;
//	  }
//	obj->getComponent<Mob>()->setEnabled(true);
//	mobs.push_back(obj->getComponent<Mob>());
//
//	++j;
//      }
//
//    Transform *t = p->getComponent<Transform>();
//    t->getPosition().setX(100);
//
//    t->getPosition().setY(300);
//    entityManager.attachComponent<SpriteRenderer>(p, "Player", "player", gu::Rect<int>(67, 3, 32, 12));
//    entityManager.attachComponent<Player>(p, "Player", 100);
//
//    entityManager.attachComponent<SpriteRenderer>(bulletobj, "Bullet", "r-typesheet1", gu::Rect<int>(249, 105, 16, 8));
//    entityManager.attachComponent<Bullet>(bulletobj, "Bullet", 1, 5);
//    entityManager.addChild(p, bulletobj);
//    Transform *tbullet = bulletobj->getComponent<Transform>();
//    tbullet->getPosition().setX(500);
//
//    r.init();
//    e.key = cu::Event::LAST_ACTION;
//    a->getComponent<ScrollingBackground>()->setEnabled(true);
//    ScrollingBackground *bg = a->getComponent<ScrollingBackground>();
//
//    p->getComponent<Player>()->setEnabled(true);
//    Player *player = p->getComponent<Player>();
//
//    bulletobj->getComponent<Bullet>()->setEnabled(true);
//    Bullet *bullet = bulletobj->getComponent<Bullet>();
//
//    while (e.key != cu::Event::ESCAPE)
//    {
//        while (i.pollEvent(e))
//        {
//            if (e.type == cu::Event::Closed)
//            {
//                std::cout << "Close button pressed" << std::endl;
//                return;
//            }
//        }
//        cmds.addCommand();
//        bg->update(BigBen::get().getElapsedtime());
//	for (auto mob : mobs)
//	  mob->update(BigBen::get().getElapsedtime());
//        player->update(BigBen::get().getElapsedtime());
//        bullet->update(BigBen::get().getElapsedtime());
//        r.draw(*a);
//	for (auto obj : objs)
//	  r.draw(*obj);
//        r.draw(*p);
//        r.draw(*bulletobj);
//        r.render();
//    }
//    std::cout << "Escape pressed" << std::endl;
//}
//
//bool stateMachineTest()
//{
//    State        ini("S0");
//    cu::Position pos1, pos2;
//
//    pos1 = cu::Position(5.0f, 5.0f);
//    pos2 = cu::Position(5.0f, 5.0f);
//
//    ini.addTransition("S2", [](cu::Position *a, cu::Position *b)
//                      {
//                          return (*a == *b);
//                      },
//                      &pos1, &pos2);
//
//    StateMachine sm(0, ini);
//
//    State s1("S1");
//    State s2("S2");
//
//    sm.setupStates(s1);
//    sm.setupStates(s2);
//
//    sm.move();
//
//    assert(sm.getCurrent().getName() == s2.getName());
//
//    return (true);
//}
//
//// bool commandSystemTest(EntityManager *entityManager)
//// {
////     CommandSystem cmds(entityManager);
////     cu::Event upEvent;
////     cu::Event downEvent;
//
////     upEvent.key = cu::Event::UP;
////     downEvent.key = cu::Event::DOWN;
//
////     cmds.addCommand(upEvent);
////     cmds.addCommand(downEvent);
////     std::cout << cmds.toString() << std::endl;
////     assert(cmds.getSize() == 2);
////     cmds.process();
////     return (true);
//// }
//
//bool mobTest()
//{
//    EntityManager entityManager;
//    GameObject    *obj = entityManager.createEntity<GameObject>("Test", 1);
//
//    entityManager.attachComponent<Transform>(obj, cu::Position(0, 0));
//    entityManager.attachComponent<Mob>(obj, "Mob", 1, 2);
//    entityManager
//            .attachComponent<SpriteRenderer>(obj, "Mob", "../res/r-typesheet19.gif", gu::Rect<int>(100, 0, 100, 300));
//    obj->getComponent<Mob>()->setEnabled(true);
//    Mob *mob = obj->getComponent<Mob>();
//    std::cout << mob->getName() << std::endl;
//    mob->update(BigBen::get().getElapsedtime());
//    // assert(obj->getComponent<Transform>()->getPosition().Y() == 200);
//    return (true);
//}

void menuTest()
{
    Renderer      r;
    Input         i(r.getWindow());
    EntityManager entityManager;
    cu::Event     e;

//	Menu menu = Menu(entityManager, e);

    //std::vector<TextField*> lRoom;

    //TextField title(gu::Rect<int>(300, 100, 800, 60), "Le R-Type officiel 2015");
    //lRoom.push_back(new TextField(gu::Rect<int>(100, 100, 300, 25), "LE ZEAUB 1"));
    //lRoom.push_back(new TextField(gu::Rect<int>(100, 200, 300, 25), "LE ZEAUB 2"));
    //lRoom.push_back(new TextField(gu::Rect<int>(100, 300, 300, 25), "LE ZEAUB 3"));
    //lRoom.push_back(new TextField(gu::Rect<int>(100, 400, 300, 25), "LE ZEAUB 4"));
    //lRoom.push_back(new TextField(gu::Rect<int>(100, 500, 300, 25), "LE ZEAUB 5"));
    //TextField refresh(gu::Rect<int>(1000, 600, 200, 25), "REFRESH");
    //TextField back(gu::Rect<int>(50, 50, 200, 25), "BACK");

    e.type = cu::Event::None;
    e.key  = cu::Event::LAST_ACTION;

    Menu *menu = entityManager.createEntity<Menu>("menu", 1, entityManager, e);
    menu->init();


    //   State initialState("Aeris");
    //   State mainMenu("MainMenu");
    //State inRoom("inRoom");

    //   initialState.addTransition("MainMenu", [](cu::Event const *e, TextField *title)
    //                              {
    //                                  return e->type == cu::Event::MouseButtonReleased && title->intersect(e->mouse.x, e->mouse.y);
    //                              },
    //                              &e, &title);

    //mainMenu.addTransition("inRoom", [](cu::Event const *e, std::vector<TextField*> &lRoom) {
    //	if (e->type == cu::Event::MouseButtonReleased)
    //		for (auto it = lRoom.begin(); it != lRoom.end(); ++it)
    //			if ((*it)->intersect(e->mouse.x, e->mouse.y))
    //				return true;
    //}, &e, lRoom);

    //inRoom.addTransition("MainMenu", [](cu::Event const *e, TextField *back)
    //{
    //	return e->type == cu::Event::MouseButtonReleased && back->intersect(e->mouse.x, e->mouse.y);
    //}, &e, &back);
    //   entityManager.attachComponent<StateMachine>(menu, initialState);
    //   entityManager.attachComponent<GUIManager>(menu);

//    menu->getComponent<ScrollingBackground>()->setEnabled(true);
//    ScrollingBackground *bg = menu->getComponent<ScrollingBackground>();
    GUIManager *gm = menu->getComponent<GUIManager>();
    r.init();

    //   gm->setupGUIElements(initialState.getName(), &title);
    //gm->setupGUIElements(mainMenu.getName(), lRoom[0]);
    //gm->setupGUIElements(mainMenu.getName(), lRoom[1]);
    //gm->setupGUIElements(mainMenu.getName(), lRoom[2]);
    //gm->setupGUIElements(mainMenu.getName(), lRoom[3]);
    //gm->setupGUIElements(mainMenu.getName(), lRoom[4]);
    //gm->setupGUIElements(mainMenu.getName(), &refresh);
    //gm->setupGUIElements(inRoom.getName(), &back);
    //sm->setupStates(mainMenu);
    //sm->setupStates(inRoom);
    //   std::cout << "Current : " << sm->getCurrent().getName() << std::endl;

    while (e.key != cu::Event::ESCAPE)
    {
        while (i.pollEvent(e))
        {
            if (e.type == cu::Event::Closed)
            {
                std::cout << "Close button pressed" << std::endl;
                return;
            }
            if (e.type == cu::Event::KeyPressed)
                std::cout << "Key pressed : " << e.key << std::endl;
            if (e.type == cu::Event::KeyReleased)
                std::cout << "Key released : " << e.key << std::endl;
            if (e.type == cu::Event::MouseButtonReleased)
                menu->move();
        }
//        bg->update(BigBen::get().getElapsedtime());
        //std::cout << "Current : " << sm->getCurrent().getName() << std::endl;
        r.draw(*menu);
        gm->draw(r.getWindow(), menu->getCurrentStateName());
        r.render();
    }
    std::cout << "Escape pressed" << std::endl;
}

void buttonAndLabelsTest()
{
    Renderer  r;
    Input     i(r.getWindow());
    TextField t(gu::Rect<float>(100, 100, 300, 25), "LE ZEAUB DE OUF");
    t.setBackColor(sf::Color::White);
    cu::Event e;


    r.getWindow().clear();
    e.key = cu::Event::LAST_ACTION;
    while (e.key != cu::Event::ESCAPE)
    {
        while (i.pollEvent(e))
        {
            if (e.type == cu::Event::Closed)
            {
                std::cout << "Close button pressed" << std::endl;
                return;
            }
            if (e.type == cu::Event::MouseButtonReleased)
            {
                std::cout << "Button "
                << e.mouse.button
                << " released : ["
                << e.mouse.x
                << ";"
                << e.mouse.y
                << "]"
                << std::endl;
            }
            if (t.intersect(e.mouse.x, e.mouse.y))
            {
                std::cout << "Click on button" << std::endl;
            }
        }
        t.draw(r.getWindow());
        r.render();
    }
    std::cout << "Escape pressed" << std::endl;
}
//
//void    RCSVParserTest()
//{
//    RCSVParser p("../res/map1.rcsv");
//    std::multimap<double, Spawn> map;
//
//    p.parse(map);
//    for (auto m : map)
//        std::cout << m.first << " => " << m.second.toString() << std::endl;
//}

int main()
{
    // EntityManager entityManager;
    //
    srand(static_cast<unsigned>(time(nullptr)));
    // if (gameObjectTest(entityManager))
    //     std::cout << "\e[32mgameObjectTest passed -> OK\e[0m" << std::endl << std::endl;
    // if (timeTest())
    //     std::cout << "\e[32mtimeTest passed -> OK\e[0m" << std::endl << std::endl;
    // if (stateMachineTest())
    //     std::cout << "\e[32mstateMachineTest passed -> OK\e[0m" << std::endl << std::endl;
    // if (commandSystemTest(&entityManager))
    //   std::cout << "\e[32mCommandSystem passed -> OK\e[0m" << std::endl;

    //buttonAndLabelsTest();
    menuTest();
    //backgroundTest();
    //RCSVParserTest();

    return 0;
}
