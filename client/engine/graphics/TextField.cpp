#include "TextField.hpp"

TextField::TextField(std::string const& str, unsigned int padding, unsigned int limit) :
        GUIElement(gu::Rect<float>(0, 0, 0, 0)), _padding(padding), _strLimit(limit)
{
    _font.loadFromFile("../res/cs_regular.ttf");
    setSize();
    setPosition();
    _backColor = sf::Color::Transparent;
    _rectShape.setFillColor(_backColor);
    _text.setFont(_font);
    _foreColor = sf::Color::Black;
    _text.setColor(_foreColor);
    setText(str);
    //_text.setString(str);
}

TextField::TextField(gu::Rect<float> const& rect, std::string const& str, unsigned int padding,
		     unsigned int limit) :
        GUIElement(rect), _padding(padding), _strLimit(limit)
{
    _font.loadFromFile("../res/cs_regular.ttf");
    setSize();
    setPosition();
    _backColor = sf::Color::Transparent;
    _rectShape.setFillColor(_backColor);
    _text.setFont(_font);
    _foreColor = sf::Color::Black;
    _text.setColor(_foreColor);
    setText(str);
    //_text.setString(str);
}

TextField::~TextField()
{ }

std::vector<const sf::Drawable *>	TextField::getDrawable() const
{
    std::vector<const sf::Drawable *> obj(0);

    obj.push_back(static_cast<const sf::Drawable *>(&_rectShape));
    obj.push_back(static_cast<const sf::Drawable *>(&_text));
    return obj;
}

void TextField::setWidth(float width)
{
    _rect.w = width;
    setSize();
}

float TextField::getWidth() const
{
    return _rect.w;
}

void TextField::setHeight(float height)
{
    _rect.h = height;
    setSize();
}

float TextField::getHeight() const
{
    return _rect.h;
}

bool TextField::setFont(const std::string& path)
{
    if (!_font.loadFromFile(path))
    {
        std::cerr << "Error loading font: " << path << std::endl;
        return false;
    }
    return true;
}

void TextField::setPosition(float posX, float posY)
{
    _rect.x = posX;
    _rect.y = posY;
    setPosition();
}

std::pair<float, float> TextField::getPosition() const
{
    return std::pair<float, float>(_rect.x, _rect.y);
}

void TextField::setText(const std::string& str)
{
    std::string tmp = _str;
    _str = str;
    _text.setString(_str);
    if (_strLimit != 0 && _text.getString().getSize() > _strLimit)
    //     (_text.getLocalBounds().width + (2 * _padding) >= _rectShape.getLocalBounds().width))
    {
        _str = tmp;
        _text.setString(tmp);
    }
}

std::string TextField::getText() const
{
    return _str;
}

void TextField::clearText()
{
  _str = "";
  _text.setString(_str);
}

void TextField::setBackColor(const sf::Color& color)
{
    _backColor = color;
    _rectShape.setFillColor(color);
}

sf::Color TextField::getBackColor() const
{
    return _backColor;
}

void TextField::setForeColor(const sf::Color& color)
{
    _foreColor = color;
    _text.setColor(color);
}

sf::Color TextField::getForeColor() const
{
    return _foreColor;
}

void TextField::setPadding(unsigned int padding)
{
    _padding = padding;
    setSize();
    setPosition();
}

unsigned int TextField::getPadding() const
{
    return _padding;
}

void    TextField::setSize()
{
    _rectShape.setSize(sf::Vector2f(_rect.w, _rect.h));
    _text.setCharacterSize((unsigned int) _rect.h - 2 * _padding);
}

void    TextField::setPosition()
{
    _rectShape.setPosition(_rect.x, _rect.y);
    _text.setPosition(_rect.x + _padding, _rect.y + _padding);
}

// TextField::TextField()
// { }

TextField::TextField(TextField const& other) : GUIElement(other._rect)
{
    _padding   = other._padding;
    _strLimit  = other._strLimit;
    _text      = other._text;
    _str       = other._str;
    _rectShape = other._rectShape;
    _font      = other._font;
}

TextField::TextField(TextField&& other) : TextField(other)
{
    swap(other);
}

TextField& TextField::operator=(TextField other)
{
    swap(other);

    return (*this);
}

void TextField::swap(TextField& other)
{
    using std::swap;

    swap(_padding, other._padding);
    swap(_strLimit, other._strLimit);
    swap(_text, other._text);
    swap(_str, other._str);
    swap(_rectShape, other._rectShape);
    swap(_font, other._font);
}

namespace std
{
    template<>
    inline void swap<TextField>(TextField &a, TextField &b)
    {
        a.swap(b);
    }
}
