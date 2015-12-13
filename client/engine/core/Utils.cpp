//
// Created by fourdr_b on 27/11/15.
//

#include <sstream>
#include <math.h>
#include "Utils.hpp"

namespace std
{
    using cu::Position;
    using cu::Rotation;
    using cu::Vector2D;
    using cu::Point2D;

    template<>
    void swap<Vector2D>(Vector2D& a, Vector2D& b)
    {
        a.swap(b);
    }

    template<>
    void swap<Point2D>(Point2D& a, Point2D& b)
    {
        a.swap(b);
    }

    //template<>
    //void swap<Position>(Position& a, Position& b)
    //{
    //    a.swap(b);
    //}

    //template<>
    //void swap<Rotation>(Rotation& a, Rotation& b)
    //{
    //    a.swap(b);
    //}
}


namespace cu
{

    Position::Position()
            : _point(0, 0)
    { }

    Position::Position(float x, float y)
            : _point(x, y)
    { }

    bool Position::operator==(Position const& other)
    {
        return (_point == other._point);
    }

    bool Position::operator!=(Position const& other)
    {
        return (!Position::operator==(other));
    }

    float Position::X() const
    {
        return _point.x;
    }

    void Position::setX(float _x)
    {
        _point.x = _x;
    }

    float Position::Y() const
    {
        return _point.y;
    }

    void Position::setY(float _y)
    {
        _point.y = _y;
    }

    Position::Position(Position const& o)
    {
        _point = o._point;
    }

    Position::Position(Position&& other) : Position(other)
    {
        swap(other);
    }

    Position& Position::operator=(Position other)
    {
        swap(other);

        return (*this);
    }

    Position::~Position()
    { }

    Rotation::Rotation()
    { }

    Rotation::Rotation(float angle)
            : _angle(angle)
    { }

    Rotation::Rotation(Rotation const& other)
    {
        _angle = other.getAngle();
    }

    Rotation::Rotation(Rotation&& other) : Rotation(other)
    {
        swap(other);
    }

    Rotation::~Rotation()
    {

    }

    Rotation& Rotation::operator=(Rotation other)
    {
        swap(other);

        return (*this);
    }

    float Rotation::getAngle() const
    {
        return _angle;
    }

    void Rotation::setAngle(float _angle)
    {
        Rotation::_angle = _angle;
    }

    bool Rotation::operator==(Rotation const& other)
    {
        return (_angle == other.getAngle());
    }

    bool Rotation::operator!=(Rotation const& other)
    {
        return (!Rotation::operator==(other));
    }

    std::string Position::toString()
    {
        std::stringstream ss;

        ss << "(" << _point.x << ", " << _point.y << ")";

        return (ss.str());
    }

    std::string Rotation::toString()
    {
        std::stringstream ss;

        ss << _angle;

        return (ss.str());
    }

    void Vector2D::swap(Vector2D& other)
    {
        using std::swap;

        swap(x, other.x);
        swap(y, other.y);
    }

    void Point2D::swap(Point2D& other)
    {
        using std::swap;

        swap(x, other.x);
        swap(y, other.y);
    }

    void Position::swap(Position& other)
    {
        using std::swap;

        swap(_point, other._point);
    }

    void Rotation::swap(Rotation& other)
    {
        using std::swap;

        swap(_angle, other._angle);
    }

//namespace std {
//    using cu::Position;
//    using cu::Rotation;
//
//    template<>
//    void swap<Position>(Position &a, Position &b)
//    {
//        a.swap(b);
//    }
//
//    template<>
//    void swap<Rotation>(Rotation&a, Rotation &b)
//    {
//        a.swap(b);
//    }
//}

    _Origin2D_ Origin2D;

    Vector2D& Vector2D::rotate(float angle)
    {
        float s = sinf(angle);
        float c = cosf(angle);

        float nx = c * x - s * y;
        float ny = s * x + c * y;

        x = nx;
        y = ny;

        return (*this);
    }

    Point2D Point2D::operator/(float t) const
    {
        float f = 1.0F / t;
        return (Point2D(x * f, y * f));
    }

    Point2D Point2D::operator*(float t) const
    {
        return (Point2D(x * t, y * t));
    }

    Vector2D Point2D::operator-(const Point2D& p) const
    {
        return (Vector2D(x - p.x, y - p.y));
    }

    Point2D Point2D::operator-(const Vector2D& v) const
    {
        return (Point2D(x - v.x, y - v.y));
    }

    Point2D Point2D::operator+(const Vector2D& v) const
    {
        return (Point2D(x + v.x, y + v.y));
    }

    Point2D Point2D::operator-(void) const
    {
        return (Point2D(-x, -y));
    }

    Point2D& Point2D::operator/=(float t)
    {
        float f = 1.0F / t;
        x *= f;
        y *= f;
        return (*this);
    }

    Point2D& Point2D::operator*=(float t)
    {
        x *= t;
        y *= t;
        return (*this);
    }

    Point2D& Point2D::operator=(Point2D v)
    {
        swap(v);

        return (*this);
    }

    Vector2D& Vector2D::normalize(void)
    {
        return (*this /= sqrtf(x * x + y * y));
    }

    bool Vector2D::operator!=(const Vector2D& v) const
    {
        return ((x != v.x) || (y != v.y));
    }

    bool Vector2D::operator==(const Vector2D& v) const
    {
        return ((x == v.x) && (y == v.y));
    }

    Vector2D Vector2D::operator&(const Vector2D& v) const
    {
        return (Vector2D(x * v.x, y * v.y));
    }

    float Vector2D::operator*(const Vector2D& v) const
    {
        return (x * v.x + y * v.y);
    }

    Vector2D Vector2D::operator/(float t) const
    {
        float f = 1.0F / t;
        return (Vector2D(x * f, y * f));
    }

    Vector2D Vector2D::operator*(float t) const
    {
        return (Vector2D(x * t, y * t));
    }

    Vector2D Vector2D::operator-(const Vector2D& v) const
    {
        return (Vector2D(x - v.x, y - v.y));
    }

    Vector2D Vector2D::operator+(const Vector2D& v) const
    {
        return (Vector2D(x + v.x, y + v.y));
    }

    Vector2D Vector2D::operator-(void) const
    {
        return (Vector2D(-x, -y));
    }

    Vector2D& Vector2D::operator&=(Vector2D v)
    {
        swap(v);

        return (*this);
    }

    Vector2D& Vector2D::operator/=(float t)
    {
        float f = 1.0F / t;

        x *= f;
        y *= f;

        return (*this);
    }

    Vector2D& Vector2D::operator*=(float t)
    {
        x *= t;
        y *= t;
        return (*this);
    }

    Vector2D& Vector2D::operator-=(Vector2D v)
    {
        swap(v);

        return (*this);
    }

    Vector2D& Vector2D::operator+=(Vector2D v)
    {
        swap(v);

        return (*this);
    }

    const float& Vector2D::operator[](long k) const
    {
        return ((&x)[k]);
    }

    float& Vector2D::operator[](long k)
    {
        return ((&x)[k]);
    }

    Vector2D& Vector2D::set(float r, float s)
    {
        x = r;
        y = s;
        return (*this);
    }

    Vector2D::Vector2D(float r, float s)
    {
        x = r;
        y = s;
    }
}

float inline SquaredMag(const cu::Vector2D& v)
{
    return (v.x * v.x + v.y * v.y);
}

float inline InverseMag(const cu::Vector2D& v)
{
    return (1.0F / sqrtf(v.x * v.x + v.y * v.y));
}

float inline Magnitude(const cu::Vector2D& v)
{
    return (sqrtf(v.x * v.x + v.y * v.y));
}

float inline dot(const cu::Vector2D& v1, const cu::Vector2D& v2)
{
    return (v1 * v2);
}

cu::Point2D inline operator*(float t, const cu::Point2D& p)
{
    return (cu::Point2D(t * p.x, t * p.y));
}

cu::Vector2D inline operator*(float t, const cu::Vector2D& v)
{
    return (cu::Vector2D(t * v.x, t * v.y));
}
