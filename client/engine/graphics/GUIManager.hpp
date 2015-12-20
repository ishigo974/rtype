#ifndef GUIMANAGER_HPP_
# define GUIMANAGER_HPP_

# include <unordered_map>
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
    void draw(sf::RenderWindow&, std::string const& state);
    virtual RTypes::my_uint16_t getMask() const;

private:
    std::unordered_map<std::string, std::vector<GUIElement *> > _scenes;
};

#endif // !GUIMANAGER_HPP_
