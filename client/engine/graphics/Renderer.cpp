#include "Renderer.hpp"

Renderer::Renderer()
{
}

void    Renderer::init()
{
    this->_res.addTexture("r-typesheet1.gif");
}

void Renderer::render()
{
    //Draw every drawable gameObjects

    this->_win.display();
}

void Renderer::draw(const GameObject& object)
{
    SpriteRenderer *sr = object.getComponent<SpriteRenderer>();
    Transform      *tr = object.getComponent<Transform>();
    sf::Sprite     sprite;

    sprite.setTexture(this->_res[sr->getPath()]);
    sprite.setTextureRect(sf::IntRect(sr->getRect().x,
                                      sr->getRect().y,
                                      sr->getRect().w,
                                      sr->getRect().h));
    sprite.setPosition(tr->getPosition().X(), tr->getPosition().Y());

    this->_win.draw(sprite);
}

Renderer::~Renderer()
{ }