#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Renderer.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"


Renderer::Renderer() :
	_win(sf::VideoMode(1280, 720), "Hey-Type",
       sf::Style::Titlebar | sf::Style::Close)
{
	_win.setFramerateLimit(60);
}

void    Renderer::init()
{
  this->_res.addTexture("../res/r-typesheet1.gif");
  this->_res.addTexture("../res/bg1.jpg", true);
  this->_res.addTexture("../res/bg2.jpg", true);
  this->_res.addTexture("../res/bg3.jpg", true);
  this->_res.addTexture("../res/bg4.jpg", true);
}

void Renderer::render()
{
	this->_win.display();
}

sf::RenderWindow& Renderer::getWindow()
{
	return _win;
}

void Renderer::draw(const GameObject& object)
{
    SpriteRenderer sr = object.renderer();
    Transform      tr = object.transform();
    sf::Sprite     sprite;

	this->_win.clear(sf::Color::White);
    sprite.setTexture(*this->_res[sr.getPath()]);
    sprite.setTextureRect(sf::IntRect(sr.getRect().x,
                                      sr.getRect().y,
                                      sr.getRect().w,
                                      sr.getRect().h));
    sprite.setPosition(tr.getPosition().X(), tr.getPosition().Y());

    this->_win.draw(sprite);
}

Renderer::~Renderer()
{ }
