#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "Renderer.hpp"


Renderer::Renderer() :
        _win(sf::VideoMode(1280, 720), "Hey-Type",
             sf::Style::Titlebar | sf::Style::Close)
{
    _win.setFramerateLimit(60);
}

void    Renderer::init()
{
    std::ifstream               file(Resources::resFile);
    std::stringstream           buf;
    boost::property_tree::ptree pt;

    if (!file)
        throw std::runtime_error("Can't retrieve resources paths: No such file: " +
                                Resources::resFile + "'");
    buf << file.rdbuf();
    file.close();
    boost::property_tree::read_json(buf, pt);

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt)
    {
        this->_res.addTexture(v.first.data(),
                            v.second.get<std::string>("path"),
                            v.second.get<bool>("repeated"));
    }
}

void Renderer::render()
{
    this->_win.display();
}

sf::RenderWindow& Renderer::getWindow()
{
    return _win;
}

gu::Rect<float>     Renderer::getFrustrum() const
{
    gu::Rect<float> frustrum;

    frustrum.w = this->_win.getView().getSize().x;
    frustrum.h = this->_win.getView().getSize().y;
    frustrum.x = this->_win.getView().getCenter().x - frustrum.w / 2;
    frustrum.y = this->_win.getView().getCenter().y - frustrum.h / 2;
    return frustrum;
}

void Renderer::draw(const GameObject& object)
{
    SpriteRenderer sr = object.renderer();
    Transform      tr = object.transform();
    sf::Sprite     sprite;

    // this->_win.clear(sf::Color::White);
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
