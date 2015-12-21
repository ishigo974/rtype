#include <SFML/Graphics.hpp>
#include <assert.h>
#include "GameObject.hpp"
#include "StateMachine.hpp"
#include "Event.hpp"
#include "EntityManager.hpp"
#include "Behaviour.hpp"
#include "Input.hpp"
#include "Event.hpp"
#include "Renderer.hpp"
#include "BigBen.hpp"
#include "ScrollingBackground.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "TextField.hpp"
#include "BehaviourSystem.hpp"
#include "GUIManager.hpp"
#include "Menu.hpp"
#include "World.hpp"
#include "PlayerObject.hpp"
#include "RTypeGame.hpp"

bool worldTest()
{
    EntityManager em;
    Renderer renderer(&em);
    Input i(renderer.getWindow());
    BehaviourSystem bs(&em);
    cu::Event   event;

    Menu *menu = em.createEntity<Menu>("Niquez-vos-races-Type", 1, &em, &event);
    menu->init();
    World w(&em, new CommandSystem(&em, &i), &renderer, &bs, &i, &event, menu);

    PlayerObject *player = em.createEntity<PlayerObject>("Player", 1, &em);
    player->init();
    GameObject *first = em.createEntity<GameObject>("LePremier", 0);
    GameObject *bg = em.createEntity<GameObject>("bg", -1);

    em.attachComponent<SpriteRenderer>(first, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));

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
   // backgroundTest();
//    testSound();

    // worldTest();
    RTypeGame game;
    game.run();
    return 0;
}
