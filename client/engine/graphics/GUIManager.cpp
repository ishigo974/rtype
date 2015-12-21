#include <iostream>
#include "GUIManager.hpp"

GUIManager::GUIManager(unsigned int id, std::string const& name) : Component(id, name)
{ }

GUIManager::~GUIManager()
{ }

void    GUIManager::addGUIElement(std::string const& state, GUIElement *gui)
{
    std::cout << "Adding an element to : " << state << std::endl;
    this->_scenes.insert(std::make_pair(state, gui));
}

void    GUIManager::draw(sf::RenderWindow& win, std::string const& state)
{
  //    std::cout << "Drawing : " << state << std::endl;

    for (auto e : _scenes)
    {
        if (e.first == state)
            e.second->draw(win);
    }
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

GUIManager::GUIManager()
{ }
