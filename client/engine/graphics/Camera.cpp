#include "Camera.hpp"

Camera::Camera(Renderer *r) :
    _renderer(r)
{}

Camera::~Camera()
{}

gu::Rect<float>     Camera::getFrustrum() const
{
    gu::Rect<float> frustrum;

    frustrum.w = this->_renderer->getWindow().getView().getSize().x;
    frustrum.h = this->_renderer->getWindow().getView().getSize().y;
    frustrum.x = this->_renderer->getWindow().getView().getCenter().x - frustrum.w / 2;
    frustrum.y = this->_renderer->getWindow().getView().getCenter().y - frustrum.h / 2;
    return frustrum;

}

void                Camera::setFrustrum(gu::Rect<float> const& frustrum)
{
    sf::View        view;

    view.setSize(frustrum.w, frustrum.h);
    view.setCenter(frustrum.x + frustrum.w / 2, frustrum.y + frustrum.h / 2);
    this->_renderer->getWindow().setView(view);
}
