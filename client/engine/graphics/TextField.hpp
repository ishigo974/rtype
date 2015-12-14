#ifndef TEXTFIELD_HPP_
# define TEXTFIELD_HPP_

# include <SFML\Graphics.hpp>
# include <iostream>

class TextField
{
public:
	TextField();
	TextField(float x, float y, float width, float height);
    ~TextField();

public:
	bool					init();
	void					draw(sf::RenderWindow &);
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
	float					_x;
	float					_y;
	float					_width;
	float					_height;
	unsigned int			_padding;
	sf::Text				_text;
	std::string				_str;
	sf::RectangleShape		_rect;
	sf::Font				_font;
};


#endif // !TEXTFIELD_HPP_