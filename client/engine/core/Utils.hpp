//
// Created by fourdr_b on 27/11/15.
//

#ifndef RTYPE_UTILS_HPP
# define RTYPE_UTILS_HPP

namespace cu
{
    class Vector2D
    {
    public:

        float x;
        float y;

        Vector2D()
        { }

        Vector2D(float r, float s);
        Vector2D& set(float r, float s);

        float      & operator[](long k);
        const float& operator[](long k) const;

        Vector2D& operator+=(Vector2D v);
        Vector2D& operator-=(Vector2D);
        Vector2D& operator*=(float t);
        Vector2D& operator/=(float t);
        Vector2D& operator&=(Vector2D v);

        Vector2D operator-(void) const;
        Vector2D operator+(const Vector2D& v) const;
        Vector2D operator-(const Vector2D& v) const;
        Vector2D operator*(float t) const;
        Vector2D operator/(float t) const;
        float    operator*(const Vector2D& v) const;
        Vector2D operator&(const Vector2D& v) const;
        bool operator==(const Vector2D& v) const;
        bool operator!=(const Vector2D& v) const;

        Vector2D& normalize(void);
        Vector2D& rotate(float angle);

        void swap(Vector2D& other);
    };


    class Point2D : public Vector2D
    {
    public:
        Point2D()
        { }

        Point2D(float r, float s) : Vector2D(r, s)
        { }

        Point2D& operator=(Point2D v);
        Point2D& operator*=(float t);
        Point2D& operator/=(float t);
        Point2D operator-(void) const;
        Point2D operator+(const Vector2D& v) const;
        Point2D  operator-(const Vector2D& v) const;
        Vector2D operator-(const Point2D& p) const;
        Point2D operator*(float t) const;
        Point2D operator/(float t) const;

        void swap(Point2D& other);
    };


    Vector2D inline operator*(float t, const Vector2D& v);
    Point2D inline  operator*(float t, const Point2D& p);
    float inline dot(const Vector2D& v1, const Vector2D& v2);
    float inline magnitude(const Vector2D& v);
    float inline inverseMag(const Vector2D& v);
    float inline squaredMag(const Vector2D& v);

    struct _Origin2D_
    {
        const Point2D& operator+(const Vector2D& v)
        {
            return (static_cast<const Point2D&>(v));
        }

        Point2D operator-(const Vector2D& v)
        {
            return (Point2D(-v.x, -v.y));
        }
    };

    class Position
    {
    public:
        Position();
        Position(float x, float y);

        Position(Position const& o);
        Position(Position&& other);
        Position& operator=(Position other);

        ~Position();

        bool operator==(Position const& other);
        bool operator!=(Position const& other);

        float X() const;
        void  setX(float _x);

        float Y() const;
        void  setY(float _y);

        std::string toString();

        void swap(Position& other);

    private:
        Point2D _point;
    };

    typedef Position Scale;

    class Rotation
    {
    public:
        Rotation();
        Rotation(float angle);

        Rotation(Rotation const& other);
        Rotation(Rotation&& other);
        Rotation& operator=(Rotation other);

        ~Rotation();

        bool operator==(Rotation const& other);
        bool operator!=(Rotation const& other);

        float getAngle() const;
        void  setAngle(float _angle);

        std::string toString();

        void swap(Rotation& other);

    private:
        float _angle;
    };

    extern _Origin2D_ Origin2D;
}

#endif //RTYPE_UTILS_HPP
