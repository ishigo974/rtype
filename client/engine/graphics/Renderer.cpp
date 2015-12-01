#include <iostream>
#include <SFML/Window.hpp>
#include "Renderer.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"


Renderer::Renderer() :
	_win(sf::VideoMode(1280, 720), "Hey-Type")
{
}

void    Renderer::init()
{
    this->_res.addTexture("r-typesheet1.gif");
}

void Renderer::render()
{
	this->_win.display();
}


void Renderer::draw(const GameObject& object)
{
    SpriteRenderer *sr = object.getComponent<SpriteRenderer>();
    Transform      *tr = object.getComponent<Transform>();
    sf::Sprite     sprite;

	if (!sr || !tr)
		return;
    sprite.setTexture(*this->_res[sr->getPath()]);
	std::cout << "ck" << std::endl;
    sprite.setTextureRect(sf::IntRect(sr->getRect().x,
                                      sr->getRect().y,
                                      sr->getRect().w,
                                      sr->getRect().h));
    sprite.setPosition(tr->getPosition().X(), tr->getPosition().Y());

    this->_win.draw(sprite);
}

Renderer::~Renderer()
{ }