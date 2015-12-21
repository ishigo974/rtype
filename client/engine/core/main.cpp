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
#include "GUIManager.hpp"
#include "Menu.hpp"

void menuTest()
{
    EntityManager entityManager;
    Renderer      r(&entityManager);
    Input         i(r.getWindow());
    cu::Event     e;

    e.type = cu::Event::None;
    e.key  = cu::Event::LAST_ACTION;

    Menu *menu = entityManager.createEntity<Menu>("menu", 1, &entityManager, &e);
    menu->init();
    r.init();

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
        r.render();
    }
    std::cout << "Escape pressed" << std::endl;
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    menuTest();
    return 0;
}
