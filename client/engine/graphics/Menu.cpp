#include "Menu.hpp"

Menu::Menu(unsigned int id, std::string const &name, int layer, EntityManager &em, cu::Event &e) :
	GameObject(id, name, layer),
	title(gu::Rect<int>(300, 100, 800, 60), "Le R-Type officiel 2015"),
	refresh(gu::Rect<int>(1000, 600, 200, 25), "REFRESH"),
	back(gu::Rect<int>(50, 50, 200, 25), "BACK")
{
	Title = State("title");
	mainMenu = State("mainMenu");
	inRoom = State("inRoom");

	rooms.push_back(new TextField(gu::Rect<int>(100, 100, 300, 25), "LE ZEAUB 1"));
	rooms.push_back(new TextField(gu::Rect<int>(100, 200, 300, 25), "LE ZEAUB 2"));
	rooms.push_back(new TextField(gu::Rect<int>(100, 300, 300, 25), "LE ZEAUB 3"));
	rooms.push_back(new TextField(gu::Rect<int>(100, 400, 300, 25), "LE ZEAUB 4"));
	rooms.push_back(new TextField(gu::Rect<int>(100, 500, 300, 25), "LE ZEAUB 5"));

	Title.addTransition("mainMenu", [](cu::Event *e, TextField *title)
	{
		return e->type == cu::Event::MouseButtonReleased &&
			title->intersect(e->mouse.x, e->mouse.y);
	}, &e, &title);

	mainMenu.addTransition("inRoom", [](cu::Event *e, std::vector<TextField*> rooms)
	{		
		if (e->type == cu::Event::MouseButtonReleased)
			for (auto it = rooms.begin(); it != rooms.end(); ++it)
				if ((*it)->intersect(e->mouse.x, e->mouse.y))
					return true;
		return false;
	}, &e, rooms);

	inRoom.addTransition("mainMenu", [](cu::Event *e, TextField *back)
	{
		return e->type == cu::Event::MouseButtonReleased && back->intersect(e->mouse.x, e->mouse.y);
	}, &e, &back);

	em.attachComponent<StateMachine>(this, Title);
	em.attachComponent<GUIManager>(this);
}

Menu::Menu(Menu const& other) :
	GameObject(other),
	title(other.title),
	refresh(other.refresh),
	back(other.back)
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

Menu::Menu()
{
	
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

void Menu::addGUIElement()
{
	GUIManager *gm = getComponent<GUIManager>();

	gm->addGUIElement(Title.getName(), &title);
	gm->addGUIElement(mainMenu.getName(), rooms[0]);
	gm->addGUIElement(mainMenu.getName(), rooms[1]);
	gm->addGUIElement(mainMenu.getName(), rooms[2]);
	gm->addGUIElement(mainMenu.getName(), rooms[3]);
	gm->addGUIElement(mainMenu.getName(), rooms[4]);
	gm->addGUIElement(mainMenu.getName(), &refresh);
	gm->addGUIElement(inRoom.getName(), &back);
}

void Menu::addState()
{
	StateMachine *sm = getComponent<StateMachine>();

	sm->addState(mainMenu);
	sm->addState(inRoom);
}

namespace std
{
	template<>
	void swap<Menu>(Menu &a, Menu &b)
	{
		a.swap(b);
	}
}
