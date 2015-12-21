#include <iostream>
#include "GUIManager.hpp"

GUIManager::GUIManager(unsigned int id) :
    Component(id, "StateMachine")
{}

GUIManager::~GUIManager() {}

void    GUIManager::addGUIElement(std::string const& state, GUIElement *gui)
{
    this->_scenes.insert(std::make_pair(state, gui));
}

std::vector<GUIElement *>   GUIManager::getGUIElements(std::string const& state)
{
    std::vector<GUIElement *> vec(0);

    for (auto obj : _scenes)
    {
        if (obj.first == state)
            vec.push_back(obj.second);
    }
    return vec;
}

RTypes::my_uint16_t GUIManager::getMask() const
{
    return Mask;
}
