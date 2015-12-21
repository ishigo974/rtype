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
#include "ObjectPool.hpp"
#include "Mob.hpp"
#include "NetworkTCP.hpp"
#include "NetworkSystem.hpp"
#include "AudioEffect.hpp"
#include "AudioEffectPlayer.hpp"
#include "Collider.hpp"
#include "Music.hpp"
#include "UDPSystem.hpp"
#include "MusicPlayer.hpp"
#include "PlayerObject.hpp"
#include "InGameEvent.hpp"
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

    PlayerObject *player = em.createEntity<PlayerObject>("Player", 2, &em);
    player->init();
    GameObject *first = em.createEntity<GameObject>("LePremier", 0);
    GameObject *bg = em.createEntity<GameObject>("bg", -1);

    em.attachComponent<SpriteRenderer>(first, "SR", "mob", gu::Rect<int>(1, 4, 32, 21));
    em.attachComponent<Mob>(first, "MobCompo");
    em.attachComponent<Collider>(first, "collision mob", 32, 21);

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
    RTypeGame game;

    game.run();
    return 0;
}
