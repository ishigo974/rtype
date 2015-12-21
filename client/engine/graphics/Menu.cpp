#include "Menu.hpp"

Menu::Menu(unsigned int id, std::string const& name, int layer, EntityManager* em, cu::Event* event) :
        GameObject(id, name, layer),
	playersInRoom(4),
        mainTitle(gu::Rect<float>(300, 100, 800, 60), "Le R-Type officiel 2015"),
        createRoom(gu::Rect<float>(1000, 540, 250, 50), "CREATE ROOM", 10),
        refresh(gu::Rect<float>(1000, 600, 200, 50), "REFRESH", 10),
        back(gu::Rect<float>(0, 0, 150, 50), "BACK", 10),
	roomTitle(gu::Rect<float>(300, 0, 640, 70), ""),
	readyField(gu::Rect<float>(1000, 600, 200, 50), "READY", 10),
	inputRoomName(gu::Rect<float>(300, 300, 800, 60), "", 10, 16),
        _event(event),
        _em(em)
{
    _titleState     = State("title");
    mainMenu        = State("mainMenu");
    inRoom          = State("inRoom");
    createRoomState = State("createRoom");
    _ready = false;
    _isVisible = true;
    
    refresh.setBackColor(sf::Color(80, 80, 80));
    createRoom.setBackColor(sf::Color(80, 80, 80));
    back.setBackColor(sf::Color(80, 80, 80));
    readyField.setBackColor(sf::Color(80, 80, 80));
    inputRoomName.setBackColor(sf::Color(80, 80, 80));

    rooms.push_back(new TextField(gu::Rect<float>(100, 100, 300, 50), "test", 10));

    playersInRoom[0] = new TextField(gu::Rect<float>(200, 150, 300, 50), "tata", 10);
    playersInRoom[0]->setForeColor(sf::Color::Red);
    playersInRoom[1] = new TextField(gu::Rect<float>(200, 250, 300, 50), "titi", 10);
    playersInRoom[1]->setForeColor(sf::Color::Red);
    playersInRoom[2] = new TextField(gu::Rect<float>(200, 350, 300, 50), "toto", 10);
    playersInRoom[2]->setForeColor(sf::Color::Red);
    playersInRoom[3] = new TextField(gu::Rect<float>(200, 450, 300, 50), "tutu", 10);
    playersInRoom[3]->setForeColor(sf::Color::Red);

    transitionToStates();

    _sm = new StateMachine(_titleState);
}

Menu::Menu(Menu const& other) :
        GameObject(other),
        mainTitle(other.mainTitle),
        refresh(other.refresh),
        back(other.back),
	roomTitle(other.roomTitle),
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
    playersInRoom.clear();
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

    swap(mainTitle, other.mainTitle);
    swap(refresh, other.refresh);
    swap(back, other.back);
    swap(roomTitle, other.roomTitle);
}

void Menu::refreshRoomList()
{
  std::cout << "Get rooms" << std::endl;
  rooms.clear();
  setupGUIElements();
}

void Menu::createNewRoom()
{
  std::cout << "Create new room" << std::endl;
}

void Menu::ready()
{
  _ready = true;
  std::cout << "Ready" << std::endl;
}

bool Menu::isReady() const
{
  return _ready;
}

bool Menu::isVisible() const
{
  return _isVisible;
}

void Menu::setVisible(bool visible)
{
  _isVisible = visible;
}

void Menu::transitionToStates()
{
    _titleState.addTransition("mainMenu", [](cu::Event *e, Menu *menu)
			      {
				if (e->type == cu::Event::MouseButtonReleased)
				  {
				    menu->refreshRoomList();
				    return true;
				  }
				return false;
			      }, _event, this);
    
    mainMenu.addTransition("inRoom", [](cu::Event *e, std::vector<TextField *> rooms,
				      TextField *rT)
			   {
			     if (e->type == cu::Event::MouseButtonReleased)
			       for (auto it = rooms.begin(); it != rooms.end(); ++it)
				 if ((*it)->intersect(e->mouse.x, e->mouse.y))
				   {
				     rT->setText((*it)->getText());
				     return (true);
				   }
			     return (false);
			   }, _event, rooms, &roomTitle);
  
    mainMenu.addTransition("createRoom", [](cu::Event *e, TextField *cR)
			   {
			     if (e->type == cu::Event::MouseButtonReleased &&
				 cR->intersect(e->mouse.x, e->mouse.y))
			       return true;
			     return false;
			   }, _event, &createRoom);
  
    mainMenu.addTransition("mainMenu", [](cu::Event *e, TextField *r, Menu *menu)
			   {
			     if (e->type == cu::Event::MouseButtonReleased &&
				 r->intersect(e->mouse.x, e->mouse.y))
			       {
				 menu->refreshRoomList();
				 return true;
			       }
			     return false;
			   }, _event, &refresh, this);
  
    createRoomState.addTransition("mainMenu", [](cu::Event *e, TextField *back, Menu *menu)
				  {
				    if (e->type == cu::Event::MouseButtonReleased &&
					back->intersect(e->mouse.x, e->mouse.y))
				      {
					menu->refreshRoomList();
					return true;
				      }
				    return false;
				  }, _event, &back, this);
  
    inRoom.addTransition("mainMenu", [](cu::Event *e, TextField *back, Menu *menu)
			 {
			   if (e->type == cu::Event::MouseButtonReleased &&
			       back->intersect(e->mouse.x, e->mouse.y))
			     {
			       menu->refreshRoomList();
			       return true;
			     }
			   return false;
			 }, _event, &back, this);

    inRoom.addTransition("inRoom", [](cu::Event *e, TextField *r, Menu *menu)
			 {
			   if (e->type == cu::Event::MouseButtonReleased &&
			       r->intersect(e->mouse.x, e->mouse.y))
			     {
			       menu->ready();
			       return true;
			     }
			   return false;
			 }, _event, &readyField, this);
}

void Menu::setupGUIElements()
{
    GUIManager *gm = getComponent<GUIManager>();

    gm->addGUIElement(_titleState.getName(), &mainTitle);

    for (auto it = rooms.begin(); it != rooms.end(); ++it)
      gm->addGUIElement(mainMenu.getName(), *it);
    
    for (auto it = playersInRoom.begin(); it != playersInRoom.end(); ++it)
      gm->addGUIElement(inRoom.getName(), *it);
    
    gm->addGUIElement(mainMenu.getName(), &refresh);
    gm->addGUIElement(mainMenu.getName(), &createRoom);
    gm->addGUIElement(createRoomState.getName(), &back);
    gm->addGUIElement(createRoomState.getName(), &inputRoomName);
    gm->addGUIElement(inRoom.getName(), &back);
    gm->addGUIElement(inRoom.getName(), &roomTitle);
    gm->addGUIElement(inRoom.getName(), &readyField);
}

void Menu::setupStates()
{
    _sm->addState(mainMenu);
    _sm->addState(inRoom);
    _sm->addState(createRoomState);
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
    str += std::to_string(rand() % 4 + 1);
    _em->attachComponent<SpriteRenderer>(this, "sr", str,
                                       gu::Rect<int>(0, 0, 1280, 720));
    _em->attachComponent<GUIManager>(this, "Manager");
    
    setupGUIElements();
    setupStates();
}
