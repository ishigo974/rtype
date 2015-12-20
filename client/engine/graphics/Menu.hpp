#ifndef MENU_HPP_
# define MENU_HPP_

# include <vector>
# include "TextField.hpp"
# include "GameObject.hpp"
# include "State.hpp"
# include "Event.hpp"
# include "EntityManager.hpp"
#include "EntityManager.hpp"
#include "StateMachine.hpp"
#include "GUIManager.hpp"

class Menu : public GameObject
{
public:
	Menu();
	Menu(unsigned int, std::string const&, int, EntityManager &, cu::Event &);
	Menu(Menu const& other);
	Menu(Menu&& other);
	Menu& operator=(Menu other);

	virtual ~Menu();

	virtual bool operator==(Menu const& other);
	virtual bool operator!=(Menu const& other);

	virtual std::string toString();

	void swap(Menu& other);

private:
	void addGUIElement();
	void addState();

private:
	std::vector<TextField*> rooms;
	TextField title;
	TextField refresh;
	TextField back;

	State Title;
	State mainMenu;
	State inRoom;
};

#endif // !MENU_HPP_