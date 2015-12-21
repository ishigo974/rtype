#include <SFML/Graphics.hpp>
#include <assert.h>
#include "GameObject.hpp"
#include "StateMachine.hpp"
#include "CommandSystem.hpp"
#include "Behaviour.hpp"
#include "Renderer.hpp"
#include "ScrollingBackground.hpp"
#include "Mob.hpp"
#include "Player.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Bullet.hpp"
#include "GUIManager.hpp"
#include "ObjectPool.hpp"
#include "NetworkTCP.hpp"
#include "NetworkSystem.hpp"
#include "AudioEffect.hpp"
#include "AudioEffectPlayer.hpp"
#include "Music.hpp"
#include "UDPSystem.hpp"
#include "MusicPlayer.hpp"
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

void renderAndInputsTest()
{
    EntityManager entityManager;
    Renderer      r(&entityManager);
    Input         i(r.getWindow());
    GameObject    *a = entityManager.createEntity<GameObject>("Test", 1);
    cu::Event     e;

    entityManager.attachComponent<Transform>(a, cu::Position(100, 100));
    entityManager.attachComponent<SpriteRenderer>(a, "lel",
                                                  "../res/r-typesheet1.gif",
                                                  gu::Rect<int>(100, 0, 100,
                                                                300));

    r.init();
    e.key = cu::Event::LAST_ACTION;

    while (e.key != cu::Event::ESCAPE)
    {
        while (i.pollEvent(e))
        {
            std::cout << "Key pressed : " << e.key << std::endl;
        }
        // r.draw(*a);
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

    EntityManager     entityManager;
    Renderer          r(&entityManager);
    Input             i(r.getWindow());
     RType::NetworkSystem networkSystem(&entityManager);
     RType::UDPSystem udpSystem(&entityManager);
     RType::NetworkTCP    *networkTCP;
     RType::Request       request;

    GameObject *gameObj = entityManager.createEntity<GameObject>("Test", 1);

    entityManager.attachComponent<RType::NetworkTCP>(gameObj, "Network");
    entityManager.attachComponent<RType::NetworkUDP>(gameObj, "UDP");

     networkTCP = gameObj->getComponent<RType::NetworkTCP>();
    GameObject        *a = entityManager.createEntity<GameObject>("Background", -1);
    cu::Event         e;
    std::stringstream ss;
    CommandSystem     cmds(&entityManager, &i);

     request.setCode(RType::Request::CL_CREATEROOM);
     request.push<std::string>("room_name", "BestRoomEver");
     networkTCP->pushRequest(request);
     networkTCP->pushRequest(RType::Request(RType::Request::CL_LISTROOMS));
     networkTCP->pushRequest(RType::Request(RType::Request::CL_READY));
     networkSystem.process();
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

    int       j = 0;
    for (auto obj : objs)
    {
        entityManager.attachComponent<SpriteRenderer>(obj, "Mob", "mob", gu::Rect<int>(1, 4, 32, 21));
        entityManager.attachComponent<Mob>(obj, "Mob", 1, 2, j % 4);
        entityManager.attachComponent<Mob>(obj, "collider");
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

    // std::cerr << "tamere" << std::endl;
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
        cmds.process();
        bg->update(BigBen::get().getElapsedtime());
        player->update(BigBen::get().getElapsedtime());
	std::vector<BulletObject *> obj = player->getActiveBullets();
	for (auto b : obj)
	  b->getComponent<Bullet>()->update(BigBen::get().getElapsedtime());
        for (auto mob : mobs)
	  mob->update(BigBen::get().getElapsedtime());
        r.render();
         udpSystem.process();
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
            .attachComponent<SpriteRenderer>(obj, "Mob",
                                             "../res/r-typesheet19.gif",
                                             gu::Rect<int>(100, 0, 100, 300));
    obj->getComponent<Mob>()->setEnabled(true);
    Mob *mob = obj->getComponent<Mob>();
    std::cout << mob->getName() << std::endl;
    mob->update(BigBen::get().getElapsedtime());
    // assert(obj->getComponent<Transform>()->getPosition().Y() == 200);
    return (true);
}

//void menuTest()
//{
//    EntityManager entityManager;
//    Renderer      r(&entityManager);
//    Input         i(r.getWindow());
//    cu::Event     e;
//
//    Label  l(gu::Rect<int>(300, 100, 160, 25), "Le R-Type officiel 2015", 64);
//    Button b(gu::Rect<int>(100, 100, 160, 25), "LE ZEAUB DE OUF", 16);
//
//    GameObject *menu = entityManager.createEntity<GameObject>("menu", 1);
//
//    std::stringstream ss;
//    ss << "menu" << rand() % 4 + 1;
//
//    entityManager.attachComponent<Transform>(menu, cu::Position(0, 0));
//    entityManager.attachComponent<SpriteRenderer>(menu, "sr", ss.str(),
//                                                  gu::Rect<int>(0, 0, 1280, 720));
//    entityManager.attachComponent<ScrollingBackground>(menu, "sb", 0);
//
//    State initialState("Aeris");
//    State mainMenu("MainMenu");
//
//    initialState.addTransition("MainMenu", [](cu::Event const *e)
//                               {
//                                   return e->type == cu::Event::KeyReleased;
//                               },
//                               &e);
//
//    entityManager.attachComponent<StateMachine>(menu, initialState);
//    entityManager.attachComponent<GUIManager>(menu);
//
//    r.init();
//    e.type = cu::Event::None;
//    e.key  = cu::Event::LAST_ACTION;
//
//    menu->getComponent<ScrollingBackground>()->setEnabled(true);
//    ScrollingBackground *bg = menu->getComponent<ScrollingBackground>();
//    StateMachine        *sm = menu->getComponent<StateMachine>();
//    GUIManager          *gm = menu->getComponent<GUIManager>();
//
//    gm->addGUIElement(initialState.getName(), &l);
//    gm->addGUIElement(mainMenu.getName(), &b);
//    sm->addState(mainMenu);
//    std::cout << "Current : " << sm->getCurrent().getName() << std::endl;
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
//            if (e.type == cu::Event::KeyPressed)
//                std::cout << "Key pressed : " << e.key << std::endl;
//            if (e.type == cu::Event::KeyReleased)
//                std::cout << "Key released : " << e.key << std::endl;
//            sm->move();
//        }
//        bg->update(BigBen::get().getElapsedtime());
//        std::cout << "Current : " << sm->getCurrent().getName() << std::endl;
//        r.draw(menu);
//        gm->draw(r.getWindow(), sm->getCurrent().getName());
//        r.render();
//    }
//    std::cout << "Escape pressed" << std::endl;
//}

// Les sf::sleep sont la pour ne pas lancer les sons en meme temps car la sfml joue les sons
// dans un thread a part; Ils seraient lanc�s en m�me temps sinon...

int audioEffectPlayerTest(GameObject *gameObj, AudioEffectPlayer& soundPlayer)
{
    AudioEffect *audio = gameObj->getComponent<AudioEffect>();
    audio->setSoundToPlay("../res/laser1.wav");
    std::cout << audio->toString() << std::endl;
    soundPlayer.play(*gameObj);
    sf::sleep(sf::milliseconds(400));

    audio->setSoundToPlay("../res/laser2.wav");
    std::cout << audio->toString() << std::endl;
    soundPlayer.play(*gameObj);
    sf::sleep(sf::milliseconds(400));

    audio->setSoundToPlay("../res/laserKIKOOLOL.wav");
    std::cout << audio->toString() << std::endl;
    soundPlayer.play(*gameObj);
    sf::sleep(sf::milliseconds(2000));

    audio->setSoundToPlay("../res/laser1.wav");
    std::cout << audio->toString() << std::endl;
    soundPlayer.play(*gameObj);
    return 0;
}

int musicPlayerTest(GameObject *gameObj, MusicPlayer& musicPlayer)
{
    Music *music = gameObj->getComponent<Music>();

    std::cout << music->toString() << std::endl;
    musicPlayer.play(*gameObj, "../res/music.wav", false);
    std::cout << music->toString() << std::endl;

    return 0;
}

int testSound()
{
    EntityManager     entity;
    MusicPlayer       musicPlayer;
    AudioEffectPlayer soundPlayer;
    GameObject        *gameObj = entity.createEntity<GameObject>("test", 1);

    entity.attachComponent<Music>(gameObj, "Music");
    entity.attachComponent<AudioEffect>(gameObj, "testAudio");

    AudioEffect *audio = gameObj->getComponent<AudioEffect>();
    audio->addSound("../res/laser1.wav");
    audio->addSound("../res/laser2.wav");
    audio->addSound("../res/laser2.wav");
    audio->addSound("DELAMERDE");
    audio->addSound("ENBOITE");

    musicPlayerTest(gameObj, musicPlayer);
    sf::sleep(sf::milliseconds(1000));

    audioEffectPlayerTest(gameObj, soundPlayer);
    while (gameObj->getComponent<Music>()->isPlaying());

    return (0);
}

#include "UDPSystem.hpp"
#include "InGameEvent.hpp"
#include "World.hpp"

void testNetwork()
{
    EntityManager        entity;
    RType::NetworkSystem networkSystem(&entity);
    RType::NetworkTCP    *networkTCP;
    RType::Request       request;
    RType::Request       tmp;
    RType::NetworkUDP *networkUDP;
    RType::UDPSystem udpSystem(&entity);

    GameObject *gameObj = entity.createEntity<GameObject>("Test", 1);

    entity.attachComponent<RType::NetworkTCP>(gameObj, "Network");
    entity.attachComponent<RType::NetworkUDP>(gameObj, "UDP");

    networkTCP = gameObj->getComponent<RType::NetworkTCP>();
    networkUDP = gameObj->getComponent<RType::NetworkUDP>();

    request.setCode(RType::Request::CL_CREATEROOM);
    request.push<std::string>("room_name", "BestRoomEver");
    networkTCP->pushRequest(request);
    networkTCP->pushRequest(RType::Request(RType::Request::CL_LISTROOMS));
    networkTCP->pushRequest(RType::Request(RType::Request::CL_READY));
    networkSystem.process();

    RType::InGameEvent             event;
    int i = 1;

    while (1)
    {
        event.setCode(RType::InGameEvent::CL_PLAYERUP);
        event.push<uint32_t>("time", i);
        networkUDP->pushRequest(event);
        udpSystem.process();
        ++i;
        event.clear();

    }
}

// bool    RCSVParserTest()
// {
//     RCSVParser p1("../res/ut_map_1.rcsv");
//     RCSVParser p2("../res/ut_map_2.rcsv");
//     RCSVParser p3("../res/ut_map_3.rcsv");
//     RCSVParser p4("../res/ut_map_4.rcsv");
//     RCSVParser p5("../res/ut_map_5.rcsv");
//     std::multimap<double, Action> map;
//     auto it = map.begin();
//     int i = 0;
//
//     p1.parse(map);
//     assert(map.find(5.0) != map.end());
//     assert(map.begin()->second.toString() == std::string("0 0 0 1300 360"));
//
//     map.clear();
//     p2.parse(map);
//     assert((it = map.find(2.3)) != map.end());
//     assert(it->second.toString() == std::string("0 0 0 1313 270.93"));
//     assert((it = map.find(9.3)) != map.end());
//     assert(it->second.toString() == std::string("0 0 0 23.32 14.32"));
//
//
//     try
//     {
//         map.clear();
//         p3.parse(map);
//     }
//     catch (std::runtime_error const&) {++i;}
//     catch (std::invalid_argument const&) {++i;}
//     try
//     {
//         map.clear();
//         p4.parse(map);
//     }
//     catch (std::runtime_error const&) {++i;}
//     catch (std::invalid_argument const&) {++i;}
//     try
//     {
//         map.clear();
//         p5.parse(map);
//     }
//     catch (std::runtime_error const&) {++i;}
//     catch (std::invalid_argument const&) {++i;}
//
//     return i == 3 ? true : false;
// }

bool worldTest()
{
    EntityManager em;
    Renderer renderer(&em);
    Input i(renderer.getWindow());
    BehaviourSystem bs(&em);
    PhysicsEngine pe(&em);

    RType::NetworkSystem networkSystem(&em);
    RType::NetworkTCP    *networkTCP;
    RType::Request       request;
    RType::Request       tmp;
    RType::NetworkUDP *networkUDP;
    RType::UDPSystem udpSystem(&em);

    World w(&em, new CommandSystem(&em, &i), &renderer, &bs, &i, &pe,
            &networkSystem, &udpSystem);

    PlayerObject *player = em.createEntity<PlayerObject>("Player", 2, &em);
    player->init();
    GameObject *first = em.createEntity<GameObject>("LePremier", 0);
    GameObject *bg = em.createEntity<GameObject>("bg", -1);

    GameObject *first2 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first3 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first4 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first5 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first6 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first7 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first8 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first9 = em.createEntity<GameObject>("LePremier", 0);
    GameObject *gameObj = em.createEntity<GameObject>("Test", 1);

    em.attachComponent<RType::NetworkTCP>(gameObj, "Network");
    em.attachComponent<RType::NetworkUDP>(gameObj, "UDP");

    networkTCP = gameObj->getComponent<RType::NetworkTCP>();
    networkUDP = gameObj->getComponent<RType::NetworkUDP>();

    request.setCode(RType::Request::CL_CREATEROOM);
    request.push<std::string>("room_name", "BestRoomEver");
    networkTCP->pushRequest(request);
    networkTCP->pushRequest(RType::Request(RType::Request::CL_LISTROOMS));
    networkTCP->pushRequest(RType::Request(RType::Request::CL_READY));

    em.attachComponent<SpriteRenderer>(first, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first, "MobCompo");
    em.attachComponent<Collider>(first, "collision mob", 32, 21);
    Transform *t = first->getComponent<Transform>();
    t->getPosition().setX(500);

    em.attachComponent<SpriteRenderer>(first2, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first2, "MobCompo");
    em.attachComponent<Collider>(first2, "collision mob", 32, 21);
    t = first2->getComponent<Transform>();
    t->getPosition().setX(400);

    em.attachComponent<SpriteRenderer>(first3, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first3, "MobCompo");
    em.attachComponent<Collider>(first3, "collision mob", 32, 21);
    t = first3->getComponent<Transform>();
    t->getPosition().setX(450);

    em.attachComponent<SpriteRenderer>(first4, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first4, "MobCompo");
    em.attachComponent<Collider>(first4, "collision mob", 32, 21);
    t = first4->getComponent<Transform>();
    t->getPosition().setX(550);

    em.attachComponent<SpriteRenderer>(first5, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first5, "MobCompo");
    em.attachComponent<Collider>(first5, "collision mob", 32, 21);
    t = first5->getComponent<Transform>();
    t->getPosition().setX(600);

    em.attachComponent<SpriteRenderer>(first6, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first6, "MobCompo");
    em.attachComponent<Collider>(first6, "collision mob", 32, 21);
    t = first6->getComponent<Transform>();
    t->getPosition().setX(650);

    em.attachComponent<SpriteRenderer>(first7, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first7, "MobCompo");
    em.attachComponent<Collider>(first7, "collision mob", 32, 21);
    t = first7->getComponent<Transform>();
    t->getPosition().setX(700);

    em.attachComponent<SpriteRenderer>(first8, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first8, "MobCompo");
    em.attachComponent<Collider>(first8, "collision mob", 32, 21);
    t = first8->getComponent<Transform>();
    t->getPosition().setX(800);

    em.attachComponent<SpriteRenderer>(first9, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first9, "MobCompo");
    em.attachComponent<Collider>(first9, "collision mob", 32, 21);
    t = first9->getComponent<Transform>();
    t->getPosition().setX(900);

    em.attachComponent<SpriteRenderer>(bg, "bg", "bg1", gu::Rect<int>(0, 0, 1280, 720));
    em.attachComponent<ScrollingBackground>(bg, "Background", 0.25);

    // w.addEntity(first);
    // w.addEntity(bg);
    // w.addEntity(player);

    w.gameLoop();

    return (true);
}

int main()
{
//     testNetwork();
//    EntityManager entityManager;
//
//    srand(static_cast<unsigned>(time(nullptr)));
//    if (gameObjectTest(entityManager))
//        std::cout << "\e[32mgameObjectTest passed -> OK\e[0m" << std::endl << std::endl;
//    if (timeTest())
//        std::cout << "\e[32mtimeTest passed -> OK\e[0m" << std::endl << std::endl;
//    if (stateMachineTest())
//        std::cout << "\e[32mstateMachineTest passed -> OK\e[0m" << std::endl << std::endl;
////    if (RCSVParserTest())
////        std::cout << "\e[32mRCSVParserTest passed -> OK\e[0m" << std::endl;
//    // buttonAndLabelsTest();
//    // menuTest();
 //   backgroundTest();
//    testSound();

    worldTest();
    return 0;
}
