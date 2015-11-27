#include "SpriteRenderer.hpp"
#include "Component.hpp"

SpriteRenderer::SpriteRenderer()
{}

SpriteRenderer::~SpriteRenderer()
{}

SpriteRenderer::SpriteRenderer(unsigned _id, std::string const& _name,
	std::string const& _path, gu::Rect<int> const& _rect)
	: Component(_id, _name), path(_path), rect(_rect)
{}

SpriteRenderer::SpriteRenderer(SpriteRenderer const& other)
	: Component(other)
{}

SpriteRenderer::SpriteRenderer(SpriteRenderer&& other)
	: SpriteRenderer(other)
{
	swap(*this, other);
}

bool SpriteRenderer::operator==(SpriteRenderer const& other)
{
	return Object::operator==(other)
		&& this->path == other.getPath()
		&& this->rect == other.getRect();
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
	std::swap(lhs.path, rhs.path);
	std::swap(lhs.rect, rhs.rect);
}

std::string const& SpriteRenderer::toString() const
{
	std::stringstream ss;

	ss << "SpriteRenderer {"
		<< "\n\tid: " << _id
		<< "\n\tname: " << _name
		<< "\n\tpath: " << path
		<< "\n\trect: " << rect.x << ", "
		<< rect.y << ", "
		<< rect.w << ", "
		<< rect.h << "\n}"
		<< std::endl;

	return ss.str();
}

const std::string& SpriteRenderer::getPath() const
{
	return this->path;
}

const gu::Rect<int>& SpriteRenderer::getRect() const
{
	return this->rect;
}
