#include "TextField.hpp"

TextField::TextField(std::string const& str, unsigned int limit) :
	GUIElement(gu::Rect<int>(0,0,0,0)), _x(0), _y(0), _width(0), _height(0), _padding(0), _strLimit(limit)
{
	_font.loadFromFile("../res/cs_regular.ttf");
	setSize();
	setPosition();
	_rect.setFillColor(sf::Color::White);
	_text.setFont(_font);
	_text.setColor(sf::Color::Black);
	setText(str);
	//_text.setString(str);
}

TextField::TextField(gu::Rect<int> const& rect, std::string const& str, unsigned int limit) :
	GUIElement(rect), _x(rect.x), _y(rect.y), _width(rect.w), _height(rect.h), _padding(0), _strLimit(limit)
{
	_font.loadFromFile("../res/cs_regular.ttf");
	setSize();
	setPosition();
	_rect.setFillColor(sf::Color::White);
	_text.setFont(_font);
	_text.setColor(sf::Color::Black);
	setText(str);
	//_text.setString(str);
}

TextField::~TextField()
{ }

void TextField::draw(sf::RenderWindow &window)
{
	window.draw(_rect);
	window.draw(_text);
}

void TextField::setWidth(float width)
{
	_width = width;
	setSize();
}

float TextField::getWidth() const
{
	return _width;
}

void TextField::setHeight(float height)
{
	_height = height;
	setSize();
}

float TextField::getHeight() const
{
	return _height;
}

bool TextField::setFont(const std::string &path)
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
	_x = posX;
	_y = posY;
	setPosition();
}

std::pair<float, float> TextField::getPosition() const
{
	return std::pair<float, float>(_x, _y);
}

void TextField::setText(const std::string &str)
{
	std::cout << "pre text: " << _text.getLocalBounds().width + (2 * _padding) << std::endl;
	std::cout << "pre rect: " << _rect.getLocalBounds().width << std::endl;

	std::string tmp = _str;
	_str = str;
	_text.setString(_str);
	if ((_strLimit != 0 && _text.getString().getSize() > _strLimit) ||
		(_text.getLocalBounds().width + (2 * _padding) >= _rect.getLocalBounds().width))
	{
		std::cout << "during text: " << _text.getLocalBounds().width + (2 * _padding) << std::endl;
		std::cout << "during rect: " << _rect.getLocalBounds().width << std::endl;
		_str = tmp;
		_text.setString(tmp);
	}
	std::cout << "post text: " << _text.getLocalBounds().width + (2 * _padding) << std::endl;
	std::cout << "post rect: " << _rect.getLocalBounds().width << std::endl << std::endl;
}

std::string TextField::getText() const
{
	return _str;
}

void TextField::setBackColor(const sf::Color &color)
{
	_rect.setFillColor(color);
}

void TextField::setForeColor(const sf::Color &color)
{
	_text.setColor(color);
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

void	TextField::setSize()
{
	_rect.setSize(sf::Vector2f(_width + (2 * _padding), _height + (2 * _padding)));
	_text.setCharacterSize((int)_height);
}

void	TextField::setPosition()
{
	_rect.setPosition(_x, _y);
	_text.setPosition(_x + _padding, _y + _padding);
}