#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer()
{ }

SpriteRenderer::~SpriteRenderer()
{ }

SpriteRenderer::SpriteRenderer(unsigned _id, std::string const& _name,
                               std::string const& _path, gu::Rect<int> const& _rect)
        : Component(_id, _name), _path(_path), _rect(_rect)
{ }

SpriteRenderer::SpriteRenderer(SpriteRenderer const& other)
        : Component(other), _path(other.getPath()), _rect(other.getRect())
{ }

SpriteRenderer::SpriteRenderer(SpriteRenderer&& other)
        : SpriteRenderer(other)
{
    swap(*this, other);
}

bool SpriteRenderer::operator==(SpriteRenderer const& other)
{
    return Object::operator==(other)
           && this->_path == other.getPath()
           && this->_rect == other.getRect();
}

bool SpriteRenderer::operator!=(SpriteRenderer const& other)
{
    return !SpriteRenderer::operator==(other);
}

SpriteRenderer& SpriteRenderer::operator=(SpriteRenderer other)
{
    swap(*this, other);

    return *this;
}

void SpriteRenderer::swap(SpriteRenderer& lhs, SpriteRenderer& rhs)
{
    std::swap(lhs._path, rhs._path);
    std::swap(lhs._rect, rhs._rect);
}

std::string SpriteRenderer::toString() const
{
    std::string ss;

    ss = "SpriteRenderer {";
    ss += "\n\tid: ";
    ss += _id;
    ss += "\n\tname: ";
    ss += _name;
    ss += "\n\tpath: ";
    ss += _path;
    ss += "\n\trect: ";
    ss += _rect.x;
    ss += ", ";
    ss += _rect.y;
    ss += ", ";
    ss += _rect.w;
    ss += ", ";
    ss += _rect.h;
    ss += "\n}\n";

    return ss;
}

const std::string& SpriteRenderer::getPath() const
{
    return this->_path;
}

void                SpriteRenderer::setPath(std::string const& s)
{
    _path = s;
}

const gu::Rect<int>& SpriteRenderer::getRect() const
{
    return this->_rect;
}

void SpriteRenderer::setRect(gu::Rect<int> const& rect)
{
	this->_rect = rect;
}

RTypes::my_uint16_t SpriteRenderer::getMask() const
{
	return Mask;
}
