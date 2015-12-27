#ifndef TEXTFIELD_HPP_
# define TEXTFIELD_HPP_

# include <SFML/Graphics.hpp>
# include <iostream>
# include "GUIElement.hpp"
# include "Rect.hpp"

class TextField : public GUIElement
{
public:
    TextField(TextField const& other);
    TextField(TextField&& other);
    TextField& operator=(TextField other);

    TextField(std::string const& text = "", unsigned int = 0,unsigned int = 0);
    TextField(gu::Rect<float> const& rect, std::string const& text = "",
              unsigned int = 0, unsigned int = 0);
    virtual ~TextField();

    void swap(TextField &other);

public:
    virtual std::vector<const sf::Drawable *>    getDrawable() const;

public:
    void                    setWidth(float);
    float                   getWidth() const;
    void                    setHeight(float);
    float                   getHeight() const;
    bool                    setFont(const std::string&);
    void                    setPosition(float, float);
    std::pair<float, float> getPosition() const;
    void                    setText(const std::string&);
    std::string             getText() const;
    void                    clearText();
    void                    setBackColor(const sf::Color&);
    sf::Color               getBackColor() const;
    void                    setForeColor(const sf::Color&);
    sf::Color               getForeColor() const;
    void                    setPadding(unsigned int);
    unsigned int            getPadding() const;

private:
    void setSize();
    void setPosition();

private:
    unsigned int       _padding;
    unsigned int       _strLimit;
    sf::Text           _text;
    std::string        _str;
    sf::RectangleShape _rectShape;
    sf::Font           _font;
    sf::Color          _backColor;
    sf::Color          _foreColor;
};

#endif // !TEXTFIELD_HPP_
