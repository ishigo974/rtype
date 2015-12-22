#include <iostream>
#include "GUIManager.hpp"

GUIManager::GUIManager()
{ }

GUIManager::GUIManager(unsigned int id, std::string const& name) : Component(id, name)
{ }

GUIManager::~GUIManager()
{ }

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

void GUIManager::onGUI()
{

}

RTypes::my_uint16_t GUIManager::getMask() const
{
    return Mask;
}

GUIManager::GUIManager(GUIManager const& other) : Component(other)
{
    _scenes = other._scenes;
}

GUIManager::GUIManager(GUIManager&& other) : GUIManager(other)
{
    swap(other);
}

void GUIManager::swap(GUIManager& other)
{
    using std::swap;

    swap(_id, other._id);
    swap(_scenes, other._scenes);
}

GUIManager& GUIManager::operator=(GUIManager other)
{
    swap(other);

    return (*this);
}

namespace std
{
    template<>
    void swap<GUIManager>(GUIManager& a, GUIManager& b)
    {
        a.swap(b);
    }
}
