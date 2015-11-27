#ifndef RECT_HPP_
# define RECT_HPP_

namespace gu
{
	template<typename T>
	struct Rect
	{
		T x;
		T y;
		T w;
		T h;

		bool operator==(const Rect& rhs)
		{
			return this->x == rhs.x
				&& this->y == rhs.y
				&& this->w == rhs.w
				&& this->h == rhs.h;
		}

		bool operator!=(const Rect& rhs)
		{
			return !Rect::operator==(rhs);
		}
	};
}

#endif // !RECT_HPP_