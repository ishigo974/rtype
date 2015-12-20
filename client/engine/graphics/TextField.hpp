#ifndef TEXTFIELD_HPP_
# define TEXTFIELD_HPP_

# include <SFML/Graphics.hpp>
# include <iostream>
# include "GUIElement.hpp"
# include "Rect.hpp"

class TextField : public GUIElement
{
public:
	TextField(std::string const& text = "", unsigned int = 0);
	TextField(gu::Rect<int> const& rect, std::string const& text = "", unsigned int = 0);
	virtual ~TextField();

public:
	virtual void			draw(sf::RenderWindow &);

public:
	void					setWidth(float);
	float					getWidth() const;
	void					setHeight(float);
	float					getHeight() const;
	bool					setFont(const std::string &);
	void					setPosition( float,  float);
	std::pair<float, float>	getPosition() const;
	void					setText(const std::string &);
	std::string				getText() const;
	void					setBackColor(const sf::Color &);
	void					setForeColor(const sf::Color &);
	void					setPadding(unsigned int);
	unsigned int			getPadding() const;

private:
	void					setSize();
	void					setPosition();

private:
	float					_x;
	float					_y;
	float					_width;
	float					_height;
	unsigned int			_padding;
	unsigned int			_strLimit;
	sf::Text				_text;
	std::string				_str;
	sf::RectangleShape		_rect;
	sf::Font				_font;

};

#endif // !TEXTFIELD_HPP_