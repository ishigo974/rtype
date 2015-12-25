#include "Menu.hpp"

Menu::Menu(unsigned int id, std::string const& name, int layer,
           EntityManager* em, cu::Event* event) :
   GameObject(id, name, layer),
   _roomsTextField(15), _playersInRoom(4),
   _mainTitle(gu::Rect<float>(300, 100, 800, 60),
             "Le R-Type officiel 2015"),
   _changeName(gu::Rect<float>(1000, 0, 250, 50), "CHANGE NAME", 10),
   _createRoom(gu::Rect<float>(1000, 590, 250, 50), "CREATE ROOM", 10),
   _refresh(gu::Rect<float>(1000, 650, 200, 50), "REFRESH", 10),
   _back(gu::Rect<float>(0, 0, 150, 50), "BACK", 10),
   _roomTitle(gu::Rect<float>(300, 0, 640, 70), ""),
   _readyField(gu::Rect<float>(1000, 600, 200, 50), "READY", 10),
   _inputRoomName(gu::Rect<float>(300, 300, 800, 50), "", 10, 16),
   _inputUserName(gu::Rect<float>(300, 300, 800, 50), "", 10, 16),
   _titleState("title"), _mainMenu("mainMenu"), _inRoom("inRoom"),
   _createRoomState("createRoom"), _changeNameState("changeName"),
   _sm(nullptr),
   _event(event),
   _em(em),
   _gm(nullptr),
   _ready(false), _isVisible(true),
   _network(nullptr),
   _done(false)
{
    initTextFields();
    transitionToStates();
    _sm = new StateMachine(_titleState);
    if ((_gm = static_cast<GameManager *>(_em->getByTag("GameManager")))
            == nullptr)
        throw std::logic_error("Could not find GameManager");
}

Menu::Menu(Menu const& other) :
        GameObject(other),
        _mainTitle(other._mainTitle),
        _refresh(other._refresh),
        _back(other._back),
        _roomTitle(other._roomTitle),
        _event(other._event),
        _done(other._done)
{}

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
    for (auto it = _roomsTextField.begin(); it != _roomsTextField.end(); ++it)
        delete *it;
    _roomsTextField.clear();
    for (auto it = _playersInRoom.begin(); it != _playersInRoom.end(); ++it)
        delete *it;
    _playersInRoom.clear();
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
    return "Menu";
}

void Menu::swap(Menu& other)
{
    using std::swap;

    swap(_mainTitle, other._mainTitle);
    swap(_refresh, other._refresh);
    swap(_back, other._back);
    swap(_roomTitle, other._roomTitle);
    // TODO: swap les autres attributs
}

void Menu::initTextFields()
{
    unsigned int    x = 100;

    _refresh.setBackColor(sf::Color(0, 0, 0, 128));
    _changeName.setBackColor(sf::Color(0, 0, 0, 128));
    _createRoom.setBackColor(sf::Color(0, 0, 0, 128));
    _back.setBackColor(sf::Color(0, 0, 0, 128));
    _readyField.setBackColor(sf::Color(0, 0, 0, 128));
    _inputRoomName.setBackColor(sf::Color(0, 0, 0, 128));
    _inputUserName.setBackColor(sf::Color(0, 0, 0, 128));

    _refresh.setForeColor(sf::Color::White);
    _changeName.setForeColor(sf::Color::White);
    _createRoom.setForeColor(sf::Color::White);
    _back.setForeColor(sf::Color::White);
    _readyField.setForeColor(sf::Color::White);
    _inputRoomName.setForeColor(sf::Color::White);
    _inputUserName.setForeColor(sf::Color::White);
    _roomTitle.setForeColor(sf::Color::White);
    _mainTitle.setForeColor(sf::Color::White);

    for (int i = 0; i < 15; ++i)
    {
        if ((i % 5) == 4)
            x += 400;
        _roomsTextField[i] =
            new TextField(gu::Rect<float>(x, (i % 5 + 1) * 100,
                                          300, 50), "", 10);
    }
    for (int i = 0; i < 4; ++i)
    {
        _playersInRoom[i] =
            new TextField(gu::Rect<float>(200, (i + 1) * 100 + 50, 300, 50),
                          "", 10);
        _playersInRoom[i]->setText("");
    }
}

void Menu::refreshRoomList()
{
    _network->pushToSend(RType::Request(RType::Request::CL_LISTROOMS));
    _lastRequest.push_back(RType::Request(RType::Request::CL_LISTROOMS));
}

void Menu::createNewRoom(std::string const &roomName)
{
    RType::Request     request;
    RType::Request::Player user;

    request.setCode(RType::Request::CL_CREATEROOM);
    request.push<std::string>("room_name", roomName);
    _network->pushToSend(request);
    _lastRequest.push_back(request);
    addPlayer(_user);
    _gm->setPlayerId(1);
    _gm->clearPlayers();
    (*_gm)[1] = nullptr;

}

void Menu::changeUserName(std::string const &username)
{
    RType::Request     request;

    request.setCode(RType::Request::CL_USERNAME);
    request.push<std::string>("username", username);
    _network->pushToSend(request);
    _lastRequest.push_back(request);
    _user.username = username;
}

void Menu::joinRoom(RType::Request::Room room)
{
    RType::Request      request;

    std::cout << "Join room: " << room.name << "ID: " << room.id << std::endl;
    request.setCode(RType::Request::CL_JOINROOM);
    request.push<unsigned int>("room_id", room.id);
    _network->pushToSend(request);
    _lastRequest.push_back(request);
}

void Menu::joinRoom(std::string const &roomName)
{
    for (auto room : _roomsList)
    {
        if (room.name == roomName)
        {
            joinRoom(room);
            break ;
        }
    }
}

void Menu::ready()
{
    bool toSet;

    toSet = (_ready == false);
    _ready = toSet;
    if (toSet)
    {
        _network->pushToSend(RType::Request(RType::Request::CL_READY));
        _lastRequest.push_back(RType::Request(RType::Request::CL_READY));
    }
    else
    {
        _network->pushToSend(RType::Request(RType::Request::CL_NOTREADY));
        _lastRequest.push_back(RType::Request(RType::Request::CL_NOTREADY));
    }
    for (auto& player : _playersList)
        if (player.id == _user.id)
            player.isReady = toSet;
    addPlayerList(_playersList);
}

void Menu::addRoom(RType::Request::Room room)
{
    _roomsList.push_back(room);
    addRoomList(_roomsList);
}

void Menu::addRoomList(RType::Request::RoomsTab const &listRoom)
{
    _roomsList = listRoom;
    for (auto it = _roomsTextField.begin(); it != _roomsTextField.end(); ++it)
    {
        (*it)->setBackColor(sf::Color::Transparent);
        (*it)->clearText();
    }
    for (int  nb = 0; nb != 10; ++nb)
    {
        if (nb < static_cast<int>(_roomsList.size()))
        {
            _roomsTextField[nb]->setText(_roomsList[nb].name);
            _roomsTextField[nb]->setBackColor(sf::Color(0, 0, 0, 128));
            _roomsTextField[nb]->setForeColor(sf::Color::White);
        }
    }
}

void Menu::addPlayer(RType::Request player)
{
    RType::Request::Player user;

    user.id = player.get<uint8_t>("player_id");
    user.username = player.get<std::string>("username");
    user.isReady = false;
    std::cout << user.username << " join room" << std::endl;
    _playersList.push_back(user);
    addPlayerList(_playersList);
}


void Menu::addPlayer(RType::Request::Player player)
{
    _playersList.push_back(player);
    addPlayerList(_playersList);
}

void Menu::addPlayerList(RType::Request::PlayersTab const &listPlayer)
{
    if (_playersList.size() == 0)
    {
        _playersList = listPlayer;
        _playersList.push_back(_user);
    }
    else
        _playersList = listPlayer;
    for (auto it = _playersInRoom.begin(); it != _playersInRoom.end(); ++it)
    {
        (*it)->setText("");
        (*it)->setBackColor(sf::Color(0, 0, 0, 128));
    }
    for (size_t nb = 0; nb < _playersList.size(); ++nb)
    {
        _playersInRoom[nb]->setText(_playersList[nb].username);
        if (_playersList[nb].isReady)
            _playersInRoom[nb]->setForeColor(sf::Color::Green);
        else
            _playersInRoom[nb]->setForeColor(sf::Color::Red);
    }
}

void Menu::userReady(RType::Request req)
{
    for (auto &player : _playersList)
    {
        if (player.id == req.get<uint8_t>("player_id"))
            player.isReady = true;
    }
    addPlayerList(_playersList);
}

bool Menu::isReady() const
{
    return _ready;
}

void Menu::deletePlayer(uint8_t id)
{
    for (auto it = _playersList.begin(); it != _playersList.end(); ++it)
    {
        if (it->id == id)
        {
            _playersList.erase(it);
            break ;
        }
    }
    addPlayerList(_playersList);
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

    _mainMenu.addTransition("inRoom", [](cu::Event *e,
                           RType::Request::RoomsTab roomsList,
                           std::vector<TextField *> rooms,
                           TextField *rT, Menu *menu)
        {
          (void)roomsList;
            if (e->type == cu::Event::MouseButtonReleased)
                for (auto it = rooms.begin(); it != rooms.end(); ++it)
                {
                    if ((*it)->getBackColor() != sf::Color::Transparent &&
                        (*it)->intersect(e->mouse.x, e->mouse.y))
                        {
                            rT->setText((*it)->getText());
                            menu->joinRoom((*it)->getText());
                            return (true);
                        }
                  }
            return (false);
        }, _event, _roomsList, _roomsTextField, &_roomTitle, this);

    _mainMenu.addTransition("changeName", [](cu::Event *e, TextField *cN)
        {
            if (e->type == cu::Event::MouseButtonReleased &&
                cN->intersect(e->mouse.x, e->mouse.y))
                  return true;
            return false;
        }, _event, &_changeName);

    _mainMenu.addTransition("createRoom", [](cu::Event *e, TextField *cR)
        {
            if (e->type == cu::Event::MouseButtonReleased &&
                cR->intersect(e->mouse.x, e->mouse.y))
            {
                return true;
            }
            return false;
        }, _event, &_createRoom);

    _mainMenu.addTransition("mainMenu", [](cu::Event *e, TextField *r, Menu *menu)
    {
        if (e->type == cu::Event::MouseButtonReleased &&
            r->intersect(e->mouse.x, e->mouse.y))
        {
            menu->refreshRoomList();
            return true;
        }
        return false;
    }, _event, &_refresh, this);

    _createRoomState.addTransition("mainMenu", [](cu::Event *e, TextField *input,
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
            else if (e->text.unicode != '\r' && e->text.unicode != '\n')
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
    }, _event, &_inputRoomName, &_back, this);

    _createRoomState.addTransition("inRoom", [](cu::Event *e, TextField *input,
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
    }, _event, &_inputRoomName, &_roomTitle, this);

    _changeNameState.addTransition("mainMenu", [](cu::Event *e, TextField *input,
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
            else if (e->text.unicode != '\r' && e->text.unicode != '\n')
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
    }, _event, &_inputUserName, &_back, this);

    _inRoom.addTransition("mainMenu", [](cu::Event *e, TextField *back,
                                        TextField *r, Menu *menu)
    {
        if (e->type == cu::Event::MouseButtonReleased &&
            back->intersect(e->mouse.x, e->mouse.y))
        {
            menu->quitRoom();
            menu->clearPlayers();
            menu->refreshRoomList();
            return true;
        }
        if (e->type == cu::Event::MouseButtonReleased &&
            r->intersect(e->mouse.x, e->mouse.y))
            menu->ready();
        return false;
    }, _event, &_back, &_readyField, this);
}

void Menu::setupGUIElements()
{
    GUIManager *gm = getComponent<GUIManager>();

    gm->addGUIElement(_titleState.getName(), &_mainTitle);

    for (auto it = _roomsTextField.begin(); it != _roomsTextField.end(); ++it)
      gm->addGUIElement(_mainMenu.getName(), *it);

    for (auto it = _playersInRoom.begin(); it != _playersInRoom.end(); ++it)
      gm->addGUIElement(_inRoom.getName(), *it);

    gm->addGUIElement(_mainMenu.getName(), &_refresh);
    gm->addGUIElement(_mainMenu.getName(), &_createRoom);
    gm->addGUIElement(_mainMenu.getName(), &_changeName);
    gm->addGUIElement(_createRoomState.getName(), &_back);
    gm->addGUIElement(_createRoomState.getName(), &_inputRoomName);
    gm->addGUIElement(_changeNameState.getName(), &_back);
    gm->addGUIElement(_changeNameState.getName(), &_inputUserName);
    gm->addGUIElement(_inRoom.getName(), &_back);
    gm->addGUIElement(_inRoom.getName(), &_roomTitle);
    gm->addGUIElement(_inRoom.getName(), &_readyField);
}

void Menu::setupStates()
{
    _sm->addState(_mainMenu);
    _sm->addState(_inRoom);
    _sm->addState(_createRoomState);
    _sm->addState(_changeNameState);
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

void Menu::update()
{
    while (_network->sizeReceive() > 0)
    {
        RType::Request tmp = _network->popReceive();
        // std::cout << "{CODE} " << tmp.getCode() << std::endl;
        switch (tmp.getCode())
        {
            case RType::Request::SE_LISTROOMS :
                addRoomList(tmp.get<RType::Request::RoomsTab>("rooms"));
                break;
            case RType::Request::SE_JOINROOM :
                addPlayer(tmp);
                break;
            case RType::Request::SE_QUITROOM :
                deletePlayer(tmp.get<uint8_t>("player_id"));
                break;
            case RType::Request::SE_CLIENTRDY :
                userReady(tmp);
                break;
            case RType::Request::SE_CLINOTRDY :
                playerNotReady(tmp.get<uint8_t>("player_id"));
                break;
            case RType::Request::SE_CLIUSRNM :
                changePlayerName(tmp);
                break;
            case RType::Request::SE_ROOMINFO :
                _user.id = tmp.get<uint8_t>("player_id");
                addPlayerList(tmp.get<RType::Request::PlayersTab>("players"));
                break;
            case RType::Request::SE_GAMESTART :
                _done = true;
                break;
            case RType::Request::SE_OK :
                break;
            case RType::Request::SE_KO :
                //TODO REVERSE STATE
                break;
            default :
                break;
        }
        if (!_lastRequest.empty())
            _lastRequest.pop_front();
    }
}

bool Menu::done() const
{
    return _done;
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

    auto tmp = _em->getByMask(TCPMask)[0];
    _network = static_cast<GameObject *>(tmp)->getComponent<TCPView>();
    setupGUIElements();
    setupStates();

    _user.id = 1;
    _user.username = "LocalPlayer";
    _user.isReady = false;
}
void Menu::clearPlayers()
{
    _playersList.clear();
}

void Menu::changePlayerName(RType::Request request)
{
    for (auto &player : _playersList)
    {
        if (player.id == request.get<uint8_t>("player_id"))
        {
            player.username = request.get<std::string>("username");
            break ;
        }
    }
    addPlayerList(_playersList);
}

void Menu::playerNotReady(uint8_t id)
{
    for (auto &player : _playersList)
    {
        if (player.id == id)
        {
            player.isReady = false;
            break ;
        }
    }
    addPlayerList(_playersList);
}

void Menu::quitRoom()
{
    _network->pushToSend(RType::Request(RType::Request::CL_QUITROOM));
    _lastRequest.push_back(RType::Request(RType::Request::CL_QUITROOM));
    _gm->clearPlayers();
}
