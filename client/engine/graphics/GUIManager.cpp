#include <iostream>
#include "GUIManager.hpp"

GUIManager::GUIManager(unsigned int id) :
    _id(id)
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
        std::cout << "scene : " << obj.first << " Asked state : " << state << std::endl;
        if (obj.first == state)
            vec.push_back(obj.second);
    }
    std::cout << "returning gui elements" << std::endl;
    return vec;
}

RTypes::my_uint16_t GUIManager::getMask() const
{
    return Mask;
}
