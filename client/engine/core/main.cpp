#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "CommandSystem.hpp"
#include "Renderer.hpp"
#include "ScrollingBackground.hpp"
#include "Mob.hpp"
#include "Player.hpp"
#include "NetworkTCP.hpp"
#include "NetworkSystem.hpp"
#include "AudioEffect.hpp"
#include "AudioEffectPlayer.hpp"
#include "PlayerObject.hpp"
#include "BehaviourSystem.hpp"
#include "PhysicsEngine.hpp"
#include "World.hpp"

bool worldTest()
{
    EntityManager   em;
    Renderer        renderer(&em);
    Input           i(renderer.getWindow());
    BehaviourSystem bs(&em);
    PhysicsEngine   pe(&em);

    RType::NetworkSystem networkSystem(&em);
    RType::Request       request;

    World w(&em, new CommandSystem(&em, &i), &renderer, &bs, &i, &pe,
            &networkSystem);

    PlayerObject *player = em.createEntity<PlayerObject>("Player", 2, &em);
    player->init();
    GameObject *first = em.createEntity<GameObject>("LePremier", 0);
    GameObject *bg    = em.createEntity<GameObject>("bg", -1);

    GameObject *first2  = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first3  = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first4  = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first5  = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first6  = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first7  = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first8  = em.createEntity<GameObject>("LePremier", 0);
    GameObject *first9  = em.createEntity<GameObject>("LePremier", 0);

    request.setCode(RType::Request::CL_CREATEROOM);
    request.push<std::string>("room_name", "BestRoomEver");

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
    worldTest();
    return 0;
}
