#include "Menu.hpp"

Menu::Menu(unsigned int id, std::string const& name, int layer,
           EntityManager* em, cu::Event* event, RType::NetworkTCP* network) :
           GameObject(id, name, layer),
           roomsTextField(15),
           playersInRoom(4),
           mainTitle(gu::Rect<float>(300, 100, 800, 60), "Le R-Type officiel 2015"),
           changeName(gu::Rect<float>(1000, 0, 250, 50), "CHANGE NAME", 10),
           createRoom(gu::Rect<float>(1000, 590, 250, 50), "CREATE ROOM", 10),
           refresh(gu::Rect<float>(1000, 650, 200, 50), "REFRESH", 10),
           back(gu::Rect<float>(0, 0, 150, 50), "BACK", 10),
           roomTitle(gu::Rect<float>(300, 0, 640, 70), ""),
           readyField(gu::Rect<float>(1000, 600, 200, 50), "READY", 10),
           inputRoomName(gu::Rect<float>(300, 300, 800, 50), "", 10, 16),
           inputUserName(gu::Rect<float>(300, 300, 800, 50), "", 10, 16),
           _event(event),
           _em(em)
{
    _titleState     = State("title");
    mainMenu        = State("mainMenu");
    inRoom          = State("inRoom");
    createRoomState = State("createRoom");
    changeNameState = State("changeName");
    _ready = false;
    _isVisible = true;
    _network = network;

    refresh.setBackColor(sf::Color(80, 80, 80));
    changeName.setBackColor(sf::Color(80, 80, 80));
    createRoom.setBackColor(sf::Color(80, 80, 80));
    back.setBackColor(sf::Color(80, 80, 80));
    readyField.setBackColor(sf::Color(80, 80, 80));
    inputRoomName.setBackColor(sf::Color(80, 80, 80));
    inputUserName.setBackColor(sf::Color(80, 80, 80));

    for (int i = 0; i < 15; ++i)
    {
      if (i >= 10)
      {
          roomsTextField[i] = new TextField(gu::Rect<float>(900, (i % 5 + 1) * 100, 300, 50), "toto", 10);
          roomsTextField[i]->setBackColor(sf::Color::Red);
      }
      else if (i >= 5)
      {
          roomsTextField[i] = new TextField(gu::Rect<float>(500, (i % 5 + 1) * 100, 300, 50), "tata", 10);
          roomsTextField[i]->setBackColor(sf::Color::Red);
      }
      else
      {
          roomsTextField[i] = new TextField(gu::Rect<float>(100, (i % 5 + 1) * 100, 300, 50), "titi", 10);
          roomsTextField[i]->setBackColor(sf::Color::Red);
      }
    }

    for (int i = 0; i < 4; ++i)
    {
        playersInRoom[i] = new TextField(gu::Rect<float>(200, (i + 1) * 100 + 50, 300, 50), "philips", 10);
        playersInRoom[i]->setForeColor(sf::Color::Red);
        playersInRoom[i]->setBackColor(sf::Color::White);
    }

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
    for (auto it = roomsTextField.begin(); it != roomsTextField.end(); ++it)
      delete *it;
    roomsTextField.clear();
    for (auto it = playersInRoom.begin(); it != playersInRoom.end(); ++it)
      delete *it;
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

std::string Menu::toString() const
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
    _network->pushRequest(RType::Request(RType::Request::CL_LISTROOMS));
}

void Menu::createNewRoom(std::string const &roomName)
{
    RType::Request     request;

    std::cout << "Create room: " << roomName << std::endl;
    request.setCode(RType::Request::CL_CREATEROOM);
    request.push<std::string>("room_name", roomName);
    _network->pushRequest(request);
}

void Menu::changeUserName(std::string const &username)
{
    RType::Request     request;

    std::cout << "Change name: " << username << std::endl;
    request.setCode(RType::Request::CL_USERNAME);
    request.push<std::string>("username", username);
    _network->pushRequest(request);
}

void Menu::joinRoom(RType::Request::Room room)
{
    RType::Request      request;

    std::cout << "Join room: " << room.name << std::endl;
    request.setCode(RType::Request::CL_JOINROOM);
    request.push<unsigned int>("room_id", room.id);
    _network->pushRequest(request);
}

void Menu::joinRoom(std::string const &room)
{
    RType::Request      request;

    std::cout << "Join room: " << room << std::endl;
    request.setCode(RType::Request::CL_JOINROOM);
    request.push<std::string>("room_name", room);
    // _network->pushRequest(request);
}

void Menu::ready()
{
    _ready = true;
    _network->pushRequest(RType::Request(RType::Request::CL_READY));
}

void Menu::addRoom(RType::Request::Room room)
{
    _roomsList.push_back(room);
    addRoomList(_roomsList);
}

void Menu::addRoomList(RType::Request::RoomsTab const &listRoom)
{
    _roomsList = listRoom;
    for (auto it = roomsTextField.begin(); it != roomsTextField.end(); ++it)
        (*it)->setBackColor(sf::Color::Transparent);
    for (int nb = 0; nb != 10; ++nb)
    {
        roomsTextField[nb]->setText(_roomsList[nb].name);
        roomsTextField[nb]->setBackColor(sf::Color(80, 80, 80));
    }
}

void Menu::addPlayer(RType::Request::Player player)
{
    _playersList.push_back(player);
    addPlayerList(_playersList);
}

void Menu::addPlayerList(RType::Request::PlayersTab const &listPlayer)
{
    _playersList = listPlayer;
    for (auto it = playersInRoom.begin(); it != playersInRoom.end(); ++it)
        (*it)->setForeColor(sf::Color::Red);
    for (int nb = 0; nb != 4; ++nb)
    {
        playersInRoom[nb]->setText(_playersList[nb].username);
        if (_playersList[nb].isReady)
            playersInRoom[nb]->setForeColor(sf::Color::Green);
    }
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

    mainMenu.addTransition("inRoom", [](cu::Event *e, RType::Request::RoomsTab roomsList,
                            std::vector<TextField *> rooms, TextField *rT, Menu *menu)
        {
          (void) roomsList;
            if (e->type == cu::Event::MouseButtonReleased)
                for (auto it = rooms.begin(); it != rooms.end(); ++it)
                  {
                    if ((*it)->getBackColor() != sf::Color::Transparent &&
                        (*it)->intersect(e->mouse.x, e->mouse.y))
                        {
                            rT->setText((*it)->getText());
                            // menu->joinRoom(roomsList[it - rooms.begin()]);
                            menu->joinRoom((*it)->getText());
                            return (true);
                        }
                  }
            return (false);
        }, _event, _roomsList, roomsTextField, &roomTitle, this);

    mainMenu.addTransition("changeName", [](cu::Event *e, TextField *cN)
        {
            if (e->type == cu::Event::MouseButtonReleased &&
                cN->intersect(e->mouse.x, e->mouse.y))
                  return true;
            return false;
        }, _event, &changeName);

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

    createRoomState.addTransition("mainMenu", [](cu::Event *e, TextField *input,
                                                 TextField *back, Menu *menu)
    {
        std::string tmp = input->getText();
        if (e->type == cu::Event::TextEntered)
        {
            if (e->text.unicode == '\b')
            {
                input->setText(tmp.substr(0, tmp.size() - 1));
                return false;
            }
            else if (e->text.unicode != '\r')
                input->setText(input->getText() +
                               static_cast<char>(e->text.unicode));
            return false;
        }
        else if (e->type == cu::Event::MouseButtonReleased &&
            back->intersect(e->mouse.x, e->mouse.y))
        {
            menu->refreshRoomList();
            input->clearText();
            return true;
        }

        return false;
    }, _event, &inputRoomName, &back, this);

    createRoomState.addTransition("inRoom", [](cu::Event *e, TextField *input,
                                              TextField *rT, Menu *menu)
    {
        std::string tmp = input->getText();
        if (e->type == cu::Event::KeyReleased && e->key == cu::Event::ENTER)
        {
            if (tmp.size() == 0)
                return false;
            menu->createNewRoom(tmp);
            rT->setText(tmp);
            input->clearText();
            return true;
        }
        return false;
    }, _event, &inputRoomName, &roomTitle, this);

    changeNameState.addTransition("mainMenu", [](cu::Event *e, TextField *input,
                                                 TextField *back, Menu *menu)
    {
        std::string tmp = input->getText();
        if (e->type == cu::Event::TextEntered)
        {
            if (e->text.unicode == '\b')
            {
                input->setText(tmp.substr(0, tmp.size() - 1));
                return false;
            }
            else if (e->text.unicode != '\r')
                input->setText(input->getText() +
                               static_cast<char>(e->text.unicode));
            return false;
        }
        else if (e->type == cu::Event::KeyReleased
                 && e->key == cu::Event::ENTER)
        {
            if (tmp.size() == 0)
              return false;
            menu->changeUserName(tmp);
            input->clearText();
            return true;
        }
        else if (e->type == cu::Event::MouseButtonReleased &&
            back->intersect(e->mouse.x, e->mouse.y))
        {
            menu->refreshRoomList();
            input->clearText();
            return true;
        }

        return false;
    }, _event, &inputUserName, &back, this);

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

    for (auto it = roomsTextField.begin(); it != roomsTextField.end(); ++it)
      gm->addGUIElement(mainMenu.getName(), *it);

    for (auto it = playersInRoom.begin(); it != playersInRoom.end(); ++it)
      gm->addGUIElement(inRoom.getName(), *it);

    gm->addGUIElement(mainMenu.getName(), &refresh);
    gm->addGUIElement(mainMenu.getName(), &createRoom);
    gm->addGUIElement(mainMenu.getName(), &changeName);
    gm->addGUIElement(createRoomState.getName(), &back);
    gm->addGUIElement(createRoomState.getName(), &inputRoomName);
    gm->addGUIElement(changeNameState.getName(), &back);
    gm->addGUIElement(changeNameState.getName(), &inputUserName);
    gm->addGUIElement(inRoom.getName(), &back);
    gm->addGUIElement(inRoom.getName(), &roomTitle);
    gm->addGUIElement(inRoom.getName(), &readyField);
}

void Menu::setupStates()
{
    _sm->addState(mainMenu);
    _sm->addState(inRoom);
    _sm->addState(createRoomState);
    _sm->addState(changeNameState);
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
