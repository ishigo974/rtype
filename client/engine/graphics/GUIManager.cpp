#include <iostream>
#include "GUIManager.hpp"

GUIManager::GUIManager(unsigned int id) :
    Component(id, "StateMachine")
{}

GUIManager::~GUIManager() {}

void    GUIManager::addGUIElement(std::string const& state, GUIElement *gui)
{
    std::cout << "Adding an element to : " << state << std::endl;
    this->_scenes[state];
    this->_scenes[state].push_back(gui);
}

void    GUIManager::draw(sf::RenderWindow& win, std::string const& state)
{
    std::cout << "Drawing : " << state << std::endl;
    for (auto it = this->_scenes[state].begin();
        it != this->_scenes[state].end();
        ++it)
    {
        (*it)->draw(win);
    }
}

RTypes::my_uint16_t GUIManager::getMask() const
{
    return Mask;
}
