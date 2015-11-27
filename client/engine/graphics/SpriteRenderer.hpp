#ifndef SPRITE_RENDERER_HPP_
# define SPRITE_RENDERER_HPP_

# include "Component.hpp"
# include "Rect.hpp"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer();
	SpriteRenderer(unsigned _id, std::string const& _name,
		std::string const& path, gu::Rect<int> const& rect);
	SpriteRenderer(SpriteRenderer const& other);
	SpriteRenderer(SpriteRenderer&& other);

protected:
	bool operator==(SpriteRenderer const& other);
	bool operator!=(SpriteRenderer const& other);
	SpriteRenderer& operator=(SpriteRenderer other);
	void swap(SpriteRenderer& lhs, SpriteRenderer& rhs);
	std::string const& toString() const;

public:
	const std::string& getPath() const;
	const gu::Rect<int>& getRect() const;

protected:
	std::string		path;
	gu::Rect<int>			rect;
};


#endif // !SPRITE_RENDERER_HPP_