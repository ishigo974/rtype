#include "Menu.hpp"

Menu::Menu(unsigned int id, std::string const& name, int layer, EntityManager& em, cu::Event& event) :
        GameObject(id, name, layer),
        title(gu::Rect<float>(300, 100, 800, 60), "Le R-Type officiel 2015"),
        refresh(gu::Rect<float>(1000, 600, 200, 25), "REFRESH"),
        back(gu::Rect<float>(50, 50, 200, 25), "BACK"),
        _event(event),
        _em(em)
{
    _titleState = State("title");
    mainMenu    = State("mainMenu");
    inRoom      = State("inRoom");

    rooms.push_back(new TextField(gu::Rect<float>(100, 100, 300, 25), "LE ZEAUB 1"));
    rooms.push_back(new TextField(gu::Rect<float>(100, 200, 300, 25), "LE ZEAUB 2"));
    rooms.push_back(new TextField(gu::Rect<float>(100, 300, 300, 25), "LE ZEAUB 3"));
    rooms.push_back(new TextField(gu::Rect<float>(100, 400, 300, 25), "LE ZEAUB 4"));
    rooms.push_back(new TextField(gu::Rect<float>(100, 500, 300, 25), "LE ZEAUB 5"));

    _titleState.addTransition("mainMenu", [](cu::Event *e, TextField *title)
    {
        return (e->type == cu::Event::MouseButtonReleased &&
                title->intersect(e->mouse.x, e->mouse.y));
    }, &event, &title);

    mainMenu.addTransition("inRoom", [](cu::Event *e, std::vector<TextField *> rooms)
    {
        if (e->type == cu::Event::MouseButtonReleased)
            for (auto it = rooms.begin(); it != rooms.end(); ++it)
                if ((*it)->intersect(e->mouse.x, e->mouse.y))
                    return (true);
        return (false);
    }, &event, rooms);

    inRoom.addTransition("mainMenu", [](cu::Event *e, TextField *back)
    {
        return e->type == cu::Event::MouseButtonReleased && back->intersect(e->mouse.x, e->mouse.y);
    }, &event, &back);

    _sm = new StateMachine(_titleState);
}

Menu::Menu(Menu const& other) :
        GameObject(other),
        title(other.title),
        refresh(other.refresh),
        back(other.back),
        _event(other._event)
{
}

Menu::Menu(Menu&& other) :
        Menu(other)
{
    swap(other);
}

Menu& Menu::operator=(Menu other)
{
    swap(other);

    return *this;
}

Menu::~Menu()
{
    rooms.clear();
}

bool Menu::operator==(Menu const& other)
{
    return Object::operator==(other);
}

bool Menu::operator!=(Menu const& other)
{
    return !Menu::operator==(other);
}

std::string Menu::toString()
{
    return std::string("Menu");
}

void Menu::swap(Menu& other)
{
    using std::swap;

    swap(title, other.title);
    swap(refresh, other.refresh);
    swap(back, other.back);
}

void Menu::setupGUIElements()
{
    GUIManager *gm = getComponent<GUIManager>();

    gm->addGUIElement(_titleState.getName(), &title);
    gm->addGUIElement(mainMenu.getName(), rooms[0]);
    gm->addGUIElement(mainMenu.getName(), rooms[1]);
    gm->addGUIElement(mainMenu.getName(), rooms[2]);
    gm->addGUIElement(mainMenu.getName(), rooms[3]);
    gm->addGUIElement(mainMenu.getName(), rooms[4]);
    gm->addGUIElement(mainMenu.getName(), &refresh);
    gm->addGUIElement(inRoom.getName(), &back);
}

void Menu::setupStates()
{
    _sm->addState(mainMenu);
    _sm->addState(inRoom);
}

namespace std
{
    template<>
    inline void swap<Menu>(Menu& a, Menu& b)
    {
        a.swap(b);
    }
}

void Menu::move()
{
    _sm->move();
}

std::string const& Menu::getCurrentStateName() const
{
    return (_sm->getCurrent().getName());
}

void Menu::init()
{
    std::string str("menu");
    str += rand() % 4 + 1;

    _em.attachComponent<SpriteRenderer>(this, "sr", str,
                                       gu::Rect<int>(0, 0, 1280, 720));
    _em.attachComponent<GUIManager>(this, "Manager");

    setupGUIElements();
    setupStates();
}
