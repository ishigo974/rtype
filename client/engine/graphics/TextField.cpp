#include "TextField.hpp"

TextField::TextField():
	_x(0), _y(0), _width(10), _height(16)
{ }

TextField::TextField(float posX, float posY, float width, float height):
	_x(posX), _y(posY), _width(width), _height(height), _padding(0)
{
}

TextField::~TextField()
{ }

bool TextField::init()
{
	if (!_font.loadFromFile("../res/arial-pixel.ttf"))
	{
		std::cerr << "Error loading font: ../res/arial-pixel.ttf" << std::endl;
		return false;
	}
	_rect.setSize(sf::Vector2f(_width + 2 * _padding, _height + 2 * _padding));
	_rect.setPosition(_x, _y);
	_rect.setFillColor(sf::Color::White);
	_text.setFont(_font);
	_text.setCharacterSize((int)_height);
	_text.setPosition(_x + _padding, _y + _padding);
	_text.setColor(sf::Color::Black);
	return true;
}

void TextField::draw(sf::RenderWindow &window)
{
	window.draw(_rect);
	window.draw(_text);
}

void TextField::setWidth(float width)
{
	_width = width;
	_rect.setSize(sf::Vector2f(_width + 2 * _padding, _height + 2 * _padding));
}

float TextField::getWidth() const
{
	return _width;
}

void TextField::setHeight(float height)
{
	_height = (height < 8 ? 8 : height);
	_text.setCharacterSize((int)_height);
	_rect.setSize(sf::Vector2f(_width + 2 * _padding, _height + 2 * _padding));
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
	_rect.setPosition(posX, posY);
	_text.setPosition(posX + _padding, posY + _padding);
}

std::pair<float, float> TextField::getPosition() const
{
	return std::pair<float, float>(_x, _y);
}

void TextField::setText(const std::string &str)
{
	std::string tmp = _str;
	_str = str;
	_text.setString(_str);
	if (_text.getLocalBounds().width > _rect.getLocalBounds().width)
	{
		_str = tmp;
		_text.setString(tmp);
	}
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
