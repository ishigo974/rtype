#ifndef GUIMANAGER_HPP_
# define GUIMANAGER_HPP_

# include <unordered_map>
# include "Component.hpp"
# include "GUIElement.hpp"
# include "Event.hpp"

class GUIManager : public Component
{
public:
    static const RTypes::my_uint16_t Mask = ComponentMask::GUIManagerMask;

public:
    GUIManager(unsigned int id);
    GUIManager(GUIManager const& other);
    GUIManager(GUIManager&& other);
    GUIManager& operator=(GUIManager other);
    virtual ~GUIManager();

    void swap(GUIManager& other);

public:
    void                        addGUIElement(std::string const& state, GUIElement *gui);
    void                        draw(sf::RenderWindow&, std::string const& state);
    virtual RTypes::my_uint16_t getMask() const;
    void                        onGUI();

private:
    unsigned int                             _id;
    std::multimap<std::string, GUIElement *> _scenes;
};

#endif // !GUIMANAGER_HPP_
