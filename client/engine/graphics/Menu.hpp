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

class Menu : public GameObject
{
public:
    Menu(unsigned int, std::string const&, int, EntityManager *, cu::Event*);
    Menu(Menu const& other);
    Menu(Menu&& other);
    Menu& operator=(Menu other);

    void init();

    virtual ~Menu();

    virtual bool operator==(Menu const& other);
    virtual bool operator!=(Menu const& other);

    virtual std::string toString();

    void swap(Menu& other);

public:
    void move();
    std::string const& getCurrentStateName() const;

private:
  void transitionToStates();
  void setupGUIElements();
  void setupStates();
  void refreshRoomList();
  void createNewRoom();
  void ready();

private:
    std::vector<TextField *> rooms;
    std::vector<TextField *> playersInRoom;
    TextField                mainTitle;
    TextField                createRoom;
    TextField                refresh;
    TextField                back;
    TextField		     roomTitle;
    TextField                readyField;
    TextField                inputRoomName;

    State		     _titleState;
    State		     mainMenu;
    State		     inRoom;
    State		     createRoomState;
  
    StateMachine *_sm;

    cu::Event     *_event;
    EntityManager *_em;
};

#endif // !MENU_HPP_
