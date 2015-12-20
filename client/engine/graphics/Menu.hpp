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
    Menu(unsigned int, std::string const&, int, EntityManager&, cu::Event&);
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
    void setupGUIElements();
    void setupStates();

private:
    std::vector<TextField *> rooms;
    TextField                title;
    TextField                refresh;
    TextField                back;

    State _titleState;
    State mainMenu;
    State inRoom;

    StateMachine *_sm;

    cu::Event&  _event;
    EntityManager _em;
};

#endif // !MENU_HPP_