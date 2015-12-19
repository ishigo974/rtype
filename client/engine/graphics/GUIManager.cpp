#include "GUIManager.hpp"

GUIManager::GUIManager(unsigned int id) :
    _id(id)
{}

GUIManager::~GUIManager() {}

void    GUIManager::addGUIElement(std::string const& state, GUIElement *gui)
{
    this->_scenes[state];
    this->_scenes[state].push_back(gui);
}

void    GUIManager::draw(sf::RenderWindow& win, std::string const& state)
{
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
