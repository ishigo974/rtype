#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <fstream>
#include "Renderer.hpp"
#include "GUIManager.hpp"
#include "GUIElement.hpp"
#include "StateMachine.hpp"

unsigned int const Renderer::width  = 1280;
unsigned int const Renderer::height = 720;

Renderer::Renderer(EntityManager *em) :
        _win(sf::VideoMode(Renderer::width, Renderer::height), "Hey-Type",
             sf::Style::Titlebar | sf::Style::Close),
        _em(em)
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

    BOOST_FOREACH(boost::property_tree::ptree::value_type& v, pt)
                {
                    this->_res.addTexture(v.first.data(),
                                          v.second.get<std::string>("path"),
                                          v.second.get<bool>("repeated"));
                }
}

void Renderer::render()
{
    this->_win.clear();

{
    auto obj = this->_em->getByMask(DrawableMask);
    std::sort(obj.begin(), obj.end(), &Renderer::comp);
    for (auto i : obj)
        this->draw(static_cast<GameObject *>(i));
}
{
    auto obj = this->_em->getByMask(GUIManagerMask);
    for (auto i : obj)
    {
        this->drawGUI(static_cast<Menu *>(i));
    }

}
    this->_win.display();
}

sf::RenderWindow& Renderer::getWindow()
{
    return _win;
}

bool      Renderer::comp(Object *a, Object *b)
{
    GameObject *p = static_cast<GameObject *>(a);
    GameObject *d = static_cast<GameObject *>(b);

    return p->getLayer() < d->getLayer();
}

void Renderer::draw(const GameObject *object)
{
    SpriteRenderer sr = object->renderer();
    Transform      tr = object->transform();
    sf::Sprite     sprite;

    sprite.setTexture(*this->_res[sr.getPath()]);
    sprite.setTextureRect(sf::IntRect(sr.getRect().x,
                                      sr.getRect().y,
                                      sr.getRect().w,
                                      sr.getRect().h));
    sprite.setPosition(tr.getPosition().X(), tr.getPosition().Y());

    this->_win.draw(sprite);
}

void Renderer::drawGUI(const Menu *object)
{
    if (!object->isVisible())
        return ;
    GUIManager      *gm = object->getComponent<GUIManager>();

    if (gm == nullptr)
        return ;

    auto vec = gm->getGUIElements(object->getCurrentStateName());
    for (auto element : vec)
    {
        auto tmp = element->getDrawable();
        for (auto drawable : tmp)
            this->_win.draw(*drawable);
    }
}

Renderer::~Renderer()
{ }
