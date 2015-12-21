#ifndef GUIMANAGER_HPP_
# define GUIMANAGER_HPP_

# include <map>
# include <vector>
# include "Component.hpp"
# include "GUIElement.hpp"

class GUIManager : public Component
{
public:
    static const RTypes::my_uint16_t Mask = ComponentMask::GUIManagerMask;

public:
    GUIManager(unsigned int id);
    virtual ~GUIManager();

public:
    void addGUIElement(std::string const& state, GUIElement *gui);
    std::vector<GUIElement *> getGUIElements(std::string const& state);
    virtual RTypes::my_uint16_t getMask() const;

private:
    unsigned int	_id;
    std::multimap<std::string, GUIElement *>    _scenes;
};

#endif // !GUIMANAGER_HPP_
