#ifndef MENU_HPP_
# define MENU_HPP_

# include <vector>
# include "TCPView.hpp"
# include "TextField.hpp"
# include "GameObject.hpp"
# include "State.hpp"
# include "Event.hpp"
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
    void move();
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

public:
    bool isReady() const;
    void addRoom(RType::Request::Room);
    void addRoomList(RType::Request::RoomsTab const &);
    void addPlayer(RType::Request player);
    void addPlayer(RType::Request::Player player);
    void addPlayerList(RType::Request::PlayersTab const &);
    void userReady(RType::Request player);
    void deletePlayer(uint8_t);
    bool isVisible() const;
    void setVisible(bool);

    void clearPlayers();

private:
    std::vector<TextField *>    roomsTextField;
    std::vector<TextField *>    playersInRoom;
    TextField                   mainTitle;
    TextField                   changeName;
    TextField                   createRoom;
    TextField                   refresh;
    TextField                   back;
    TextField                   roomTitle;
    TextField                   readyField;
    TextField                   inputRoomName;
    TextField                   inputUserName;

    State		                _titleState;
    State		                mainMenu;
    State		                inRoom;
    State		                createRoomState;
    State                       changeNameState;

    StateMachine	            *_sm;

    cu::Event		            *_event;
    EntityManager	            *_em;
    bool		                _ready;
    bool		                _isVisible;
    TCPView*	                _network;
    RType::Request::RoomsTab    _roomsList;
    RType::Request::PlayersTab  _playersList;

    RType::Request::Player      _user;
};

#endif // !MENU_HPP_
