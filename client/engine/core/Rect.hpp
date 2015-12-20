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

        Rect()
        { };

        Rect(const T& x, const T& y, const T& w, const T& h)
                : x(x), y(y), w(w), h(h)
        { }

        bool operator==(const Rect& rhs)
        {
            return (this->x == rhs.x
                    && this->y == rhs.y
                    && this->w == rhs.w
                    && this->h == rhs.h);
        }

        bool operator!=(const Rect& rhs)
        {
            return !Rect::operator==(rhs);
        }

        bool intersects(Rect const& other)
        {
            return (x < other.x + other.w &&
                    x + w > other.x &&
                    y < other.y + other.h &&
                    h + y > other.y);
        }
    };
}

#endif // !RECT_HPP_