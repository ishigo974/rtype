#ifndef MENU_HPP_
# define MENU_HPP_

# include <vector>
# include "TextField.hpp"
# include "GameObject.hpp"
# include "State.hpp"
# include "Event.hpp"
# include "EntityManager.hpp"
# include "StateMachine.hpp"
# include "GUIManager.hpp"
# include "NetworkTCP.hpp"
//# include "Request.hpp"

class Menu : public GameObject
{
public:
    Menu(unsigned int, std::string const&, int, EntityManager*, cu::Event*,
         RType::NetworkTCP* network);
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
    void joinRoom(RType::Request::Room);
    void ready();

public:
    bool isReady() const;
    void addRoom(RType::Request::Room);
    void addRoomList(RType::Request::RoomsTab const &);
    bool isVisible() const;
    void setVisible(bool);

private:
    std::vector<TextField *> roomsTextField;
    std::vector<TextField *> playersInRoom;
    TextField                mainTitle;
    TextField                createRoom;
    TextField                refresh;
    TextField                back;
    TextField                roomTitle;
    TextField                readyField;
    TextField                inputRoomName;

    State		                 _titleState;
    State		                 mainMenu;
    State		                 inRoom;
    State		                 createRoomState;

    StateMachine	           *_sm;

    cu::Event		             *_event;
    EntityManager	           *_em;
    bool		                 _ready;
    bool		                 _isVisible;
    RType::NetworkTCP*	     _network;
    RType::Request::RoomsTab _roomsList;
};

#endif // !MENU_HPP_
