#ifndef SPRITE_RENDERER_HPP_
# define SPRITE_RENDERER_HPP_

# include "Component.hpp"
# include "Rect.hpp"

class SpriteRenderer : public Component
{
public:
  SpriteRenderer();
  SpriteRenderer(unsigned _id, std::string const& _name,
                 std::string const& path, gu::Rect<int> const& rect);
  SpriteRenderer& operator=(SpriteRenderer other);
  SpriteRenderer(SpriteRenderer const& other);
  SpriteRenderer(SpriteRenderer&& other);
  ~SpriteRenderer();

  bool                operator==(SpriteRenderer const& other);
  bool                operator!=(SpriteRenderer const& other);

  void swap(SpriteRenderer& lhs, SpriteRenderer& rhs);

  std::string toString() const;

  std::string const&   getPath() const;
  gu::Rect<int> const& getRect() const;
  void setRect(gu::Rect<int> const&);
  RTypes::my_uint16_t	getMask() const;

public:
  static RTypes::my_uint16_t const Mask = 128;

protected:
  std::string   _path;
  gu::Rect<int> _rect;
};


#endif // !SPRITE_RENDERER_HPP_
