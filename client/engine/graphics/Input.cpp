#include "Input.hpp"
#include "Event.hpp"

Input::Input(sf::RenderWindow& win) :
  _win(win), _bindings(cu::Event::LAST_ACTION),
  _focus(true)
{
  _bindings[cu::Event::UP] = sf::Keyboard::Up;
  _bindings[cu::Event::RIGHT] = sf::Keyboard::Right;
  _bindings[cu::Event::DOWN] = sf::Keyboard::Down;
  _bindings[cu::Event::LEFT] = sf::Keyboard::Left;
  _bindings[cu::Event::SHOOT] = sf::Keyboard::Space;
  _bindings[cu::Event::ESCAPE] = sf::Keyboard::Escape;
}

Input::~Input()
{
}

bool Input::isKeyPressed(cu::Event::KeyEvent key)
{
  if (!_focus)
    return false;
  return sf::Keyboard::isKeyPressed(_bindings[key]);
}

bool Input::pollEvent(cu::Event& event)
{
  sf::Event		e;

  if (!_win.pollEvent(e))
    return false;
  switch (e.type)
    {
    case sf::Event::KeyPressed:
      event.type = cu::Event::KeyPressed;
      return key(e, event);
    case sf::Event::KeyReleased:
      event.type = cu::Event::KeyReleased;
      return key(e, event);
    case sf::Event::MouseButtonPressed:
      event.type = cu::Event::MouseButtonPressed;
      return mouse(e, event);
    case sf::Event::MouseButtonReleased:
      event.type = cu::Event::MouseButtonReleased;
      return mouse(e, event);
    case sf::Event::Closed:
      event.type = cu::Event::Closed;
      return true;
    case sf::Event::GainedFocus:
      _focus = true;
      return true;
    case sf::Event::LostFocus:
      _focus = true;
      return true;
    default:
      return false;
    }
}

bool Input::key(sf::Event const& e, cu::Event& event)
{
  unsigned int	i;

  for (i = cu::Event::UP; i != cu::Event::LAST_ACTION; ++i)
    {
      if (e.key.code == _bindings[i])
	{
	  event.key = static_cast<cu::Event::KeyEvent>(i);
	  return true;
	}
    }
  return false;
}

bool Input::mouse(sf::Event const& e, cu::Event& event)
{
  if (e.mouseButton.button >= sf::Mouse::Button::Left
      && e.mouseButton.button <= sf::Mouse::Button::Middle)
    {
      event.mouse.button = static_cast<cu::Event::MouseButton>(e.mouseButton.button);
      event.mouse.x = e.mouseButton.x;
      event.mouse.y = e.mouseButton.y;
      return true;
    }
  return false;
}
