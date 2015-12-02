#include "Input.hpp"

Input::Input(sf::RenderWindow& win) :
	_win(win), _bindings(cu::Event::LAST_ACTION)
{
	_bindings[cu::Event::UP] = sf::Keyboard::Up;
	_bindings[cu::Event::RIGHT] = sf::Keyboard::Right;
	_bindings[cu::Event::DOWN] = sf::Keyboard::Down;
	_bindings[cu::Event::LEFT] = sf::Keyboard::Left;
	_bindings[cu::Event::SHOOT] = sf::Keyboard::Space;
}

Input::~Input()
{
}

bool Input::pollEvent(cu::Event& event)
{
	sf::Event		e;

	if (!_win.pollEvent(e))
		return false;
	switch (e.type)
	{
		case sf::Event::KeyPressed:
			return keyPressed(e, event);
			break;
		default:
			return false;
	}
}

bool Input::keyPressed(sf::Event const& e, cu::Event& event)
{
	unsigned int	i;

	for (i = cu::Event::UP; i != cu::Event::LAST_ACTION; ++i)
	{
		if (e.KeyPressed == _bindings[i])
		{
			event.key = static_cast<cu::Event::KeyEvent>(i);
			return true;
		}
	}
	return false;
}
