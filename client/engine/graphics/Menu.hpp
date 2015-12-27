#ifndef MENU_HPP_
# define MENU_HPP_

# include <vector>
# include "TCPView.hpp"
# include "TextField.hpp"
# include "GameObject.hpp"
# include "State.hpp"
# include "Event.hpp"
# include "GameManager.hpp"
# include "EntityManager.hpp"
# include "StateMachine.hpp"
# include "GUIManager.hpp"
# include "NetworkTCP.hpp"

class Menu : public GameObject
{
public:
    Menu(unsigned int, std::string const&, int, EntityManager*, cu::Event*);
    Menu(Menu const& other);
    Menu(Menu&& other);
    Menu& operator=(Menu other);

    void init();

    virtual ~Menu();

    virtual bool operator==(Menu const& other);
    virtual bool operator!=(Menu const& other);

    virtual std::string toString() const;

    void swap(Menu& other);

public:
    void initTextFields();
    void move();
    void update();
    bool done() const;
    std::string const& getCurrentStateName() const;

private:
    void transitionToStates();
    void setupGUIElements();
    void setupStates();
    void refreshRoomList();
    void createNewRoom(std::string const &);
    void changeUserName(std::string const &);
    void joinRoom(RType::Request::Room);
    void joinRoom(std::string const &);
    void ready();
    void quitRoom();

public:
    bool isReady() const;
    void addRoom(RType::Request::Room);
    void addRoomList(RType::Request::RoomsTab const &);
    void addPlayer(RType::Request player);
    void addPlayer(RType::Request::Player player);
    void addPlayerList(RType::Request::PlayersTab const &);
    void userReady(RType::Request player);
    void deletePlayer(uint8_t);
    void changePlayerName(RType::Request);
    void playerNotReady(uint8_t);
    void clearPlayers();
	void endGame(RType::Request::ScoresTab const &scores);

private:
    std::vector<TextField *>    _roomsTextField;
    std::vector<TextField *>    _playersInRoom;
    std::vector<TextField *>    _scores;

    TextField                   _mainTitle;
    TextField                   _changeName;
    TextField                   _createRoom;
    TextField                   _refresh;
    TextField                   _continue;
    TextField                   _back;
    TextField                   _roomTitle;
    TextField                   _readyField;
    TextField                   _inputRoomName;
    TextField                   _inputUserName;

    State                       _titleState;
    State                       _mainMenu;
    State                       _inRoom;
    State                       _createRoomState;
    State                       _changeNameState;
    State                       _endGameState;

    StateMachine*               _sm;

    cu::Event*                  _event;
    EntityManager*              _em;
    GameManager*                _gm;
    bool                        _ready;
    bool                        _isVisible;
    TCPView*                    _network;
    RType::Request::RoomsTab    _roomsList;
    RType::Request::PlayersTab  _playersList;

    RType::Request::Player      _user;
    std::deque<RType::Request>  _lastRequest;

    bool                        _done;
};

#endif // !MENU_HPP_
