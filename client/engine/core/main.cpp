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
#include "Label.hpp"
#include "Button.hpp"
#include "Bullet.hpp"
#include "GUIManager.hpp"
#include "ObjectPool.hpp"
#include "RCSVParser.hpp"
#include "PlayerObject.hpp"

bool gameObjectTest(EntityManager& entityManager)
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
    EntityManager     entityManager;
    Renderer          r(&entityManager);
    Input             i(r.getWindow());

    GameObject        *a = entityManager.createEntity<GameObject>("Background", -1);
    cu::Event         e;
    std::stringstream ss;
    CommandSystem     cmds(&entityManager, &i);
    ss << "bg" << rand() % 4 + 1;

    PlayerObject *p   = entityManager.createEntity<PlayerObject>("Player", 10, &entityManager);
    p->init();

    std::vector<GameObject *>	objs;
    std::vector<Mob *>	mobs;
    objs.push_back(entityManager.createEntity<GameObject>("Mob", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob4", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob4", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob2", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob3", 3));
    objs.push_back(entityManager.createEntity<GameObject>("Mob4", 3));


    entityManager.attachComponent<SpriteRenderer>(a, "lel", ss.str(), gu::Rect<int>(0, 0, 1280, 720));
    entityManager.attachComponent<ScrollingBackground>(a, "lal", 60);

    int j = 0;
    for (auto obj : objs)
    {
        entityManager.attachComponent<SpriteRenderer>(obj, "Mob", "mob", gu::Rect<int>(1, 4, 32, 21));
        entityManager.attachComponent<Mob>(obj, "Mob", 1, 2, j % 4);
        Transform *t = obj->getComponent<Transform>();
        t->getPosition().setX(Renderer::width - 32);
	switch (j)
	  {
	  case 0:
	    t->getPosition().setX(rand() % (Renderer::width - 32));
	    t->getPosition().setY(rand() % (Renderer::height - 21));
	    break;
	  case 1:
	    t->getPosition().setY(rand() % (Renderer::height - 21));
        break;
	  case 2:
	    t->getPosition().setY(rand() % (Renderer::height - 21));
	    break;
	  case 3:
	    t->getPosition().setY(rand() % (Renderer::height - 21));
	    break;
	  default:
	    break;
	  }
	obj->getComponent<Mob>()->setEnabled(true);
	mobs.push_back(obj->getComponent<Mob>());

	++j;
      }

    r.init();
    e.key = cu::Event::LAST_ACTION;
    a->getComponent<ScrollingBackground>()->setEnabled(true);
    ScrollingBackground *bg = a->getComponent<ScrollingBackground>();

    Player *player = p->getComponent<Player>();

    while (e.key != cu::Event::ESCAPE)
    {
        while (i.pollEvent(e))
        {
            if (e.type == cu::Event::Closed)
            {
                std::cout << "Close button pressed" << std::endl;
                return;
            }
        }
        cmds.addCommand();
        bg->update(BigBen::get().getElapsedtime());
        player->update(BigBen::get().getElapsedtime());
	std::vector<BulletObject *> obj = player->getActiveBullets();
	for (auto b : obj)
	  b->getComponent<Bullet>()->update(BigBen::get().getElapsedtime());
        for (auto mob : mobs)
	  mob->update(BigBen::get().getElapsedtime());
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

    ini.addTransition("S2", [](cu::Position *a, cu::Position *b)
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

bool mobTest()
{
    EntityManager entityManager;
    GameObject    *obj = entityManager.createEntity<GameObject>("Test", 3);

    entityManager.attachComponent<Transform>(obj, cu::Position(0, 0));
    entityManager.attachComponent<Mob>(obj, "Mob", 1, 2);
    entityManager
            .attachComponent<SpriteRenderer>(obj, "Mob", "../res/r-typesheet19.gif", gu::Rect<int>(100, 0, 100, 300));
    obj->getComponent<Mob>()->setEnabled(true);
    Mob *mob = obj->getComponent<Mob>();
    std::cout << mob->getName() << std::endl;
    mob->update(BigBen::get().getElapsedtime());
    // assert(obj->getComponent<Transform>()->getPosition().Y() == 200);
    return (true);
}

void menuTest()
{
    EntityManager entityManager;
    Renderer      r(&entityManager);
    Input         i(r.getWindow());
    cu::Event     e;

    Label l(gu::Rect<int>(300, 100, 160, 25), "Le R-Type officiel 2015", 64);
    Button b(gu::Rect<int>(100, 100, 160, 25), "LE ZEAUB DE OUF", 16);

    GameObject *menu = entityManager.createEntity<GameObject>("menu", 1);

    std::stringstream ss;
    ss << "menu" << rand() % 4 + 1;

    entityManager.attachComponent<Transform>(menu, cu::Position(0, 0));
    entityManager.attachComponent<SpriteRenderer>(menu, "sr", ss.str(),
                                                  gu::Rect<int>(0, 0, 1280, 720));
    entityManager.attachComponent<ScrollingBackground>(menu, "sb", 0);

    State initialState("Aeris");
    State mainMenu("MainMenu");

    initialState.addTransition("MainMenu", [](cu::Event const *e)
                               {
                                   return e->type == cu::Event::KeyReleased;
                               },
                               &e);

    entityManager.attachComponent<StateMachine>(menu, initialState);
    entityManager.attachComponent<GUIManager>(menu);

    r.init();
    e.type = cu::Event::None;
    e.key  = cu::Event::LAST_ACTION;

    menu->getComponent<ScrollingBackground>()->setEnabled(true);
    ScrollingBackground *bg = menu->getComponent<ScrollingBackground>();
    StateMachine        *sm = menu->getComponent<StateMachine>();
    GUIManager          *gm = menu->getComponent<GUIManager>();

    gm->addGUIElement(initialState.getName(), &l);
    gm->addGUIElement(mainMenu.getName(), &b);
    sm->addState(mainMenu);
    // std::cout << "Current : " << sm->getCurrent().getName() << std::endl;

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
            sm->move();
        }
        bg->update(BigBen::get().getElapsedtime());
        // std::cout << "Current : " << sm->getCurrent().getName() << std::endl;
        // r.draw(menu);
        // gm->draw(r.getWindow(), sm->getCurrent().getName());
        r.render();
    }
    std::cout << "Escape pressed" << std::endl;
}

bool    RCSVParserTest()
{
    RCSVParser p1("../res/ut_map_1.rcsv");
    RCSVParser p2("../res/ut_map_2.rcsv");
    RCSVParser p3("../res/ut_map_3.rcsv");
    RCSVParser p4("../res/ut_map_4.rcsv");
    RCSVParser p5("../res/ut_map_5.rcsv");
    std::multimap<double, Action> map;
    auto it = map.begin();
    int i = 0;

    p1.parse(map);
    assert(map.find(5.0) != map.end());
    assert(map.begin()->second.toString() == std::string("0 0 0 1300 360"));

    map.clear();
    p2.parse(map);
    assert((it = map.find(2.3)) != map.end());
    assert(it->second.toString() == std::string("0 0 0 1313 270.93"));
    assert((it = map.find(9.3)) != map.end());
    assert(it->second.toString() == std::string("0 0 0 23.32 14.32"));


    try
    {
        map.clear();
        p3.parse(map);
    }
    catch (std::runtime_error const&) {++i;}
    catch (std::invalid_argument const&) {++i;}
    try
    {
        map.clear();
        p4.parse(map);
    }
    catch (std::runtime_error const&) {++i;}
    catch (std::invalid_argument const&) {++i;}
    try
    {
        map.clear();
        p5.parse(map);
    }
    catch (std::runtime_error const&) {++i;}
    catch (std::invalid_argument const&) {++i;}

    return i == 3 ? true : false;
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
    if (RCSVParserTest())
        std::cout << "\e[32mRCSVParserTest passed -> OK\e[0m" << std::endl;
    menuTest();
    backgroundTest();
    RCSVParserTest();

    return 0;
}
