#ifndef GUIMANAGER_HPP_
# define GUIMANAGER_HPP_

# include <map>
# include <vector>
# include "Component.hpp"
# include "GUIElement.hpp"
# include "Event.hpp"

class GUIManager : public Component
{
public:
    static const RTypes::my_uint16_t Mask = ComponentMask::GUIManagerMask;

public:
    GUIManager();
    GUIManager(unsigned int id, std::string const& name);
    GUIManager(GUIManager const& other);
    GUIManager(GUIManager&& other);
    GUIManager& operator=(GUIManager other);
    virtual ~GUIManager();

    void swap(GUIManager& other);

public:
    void addGUIElement(std::string const& state, GUIElement *gui);
    std::vector<GUIElement *> getGUIElements(std::string const& state);
    virtual RTypes::my_uint16_t getMask() const;
    void                        onGUI();

private:
    unsigned int                             _id;
    std::multimap<std::string, GUIElement *> _scenes;
};

#endif // !GUIMANAGER_HPP_
