//
// Created by fourdr_b on 27/11/15.
//

#include <sstream>
#include "Utils.hpp"

namespace cu
{

    Position::Position()
    { }

    Position::Position(float x, float y)
            : _x(x), _y(y)
    { }

    bool Position::operator==(Position const& other)
    {
        return (_x == other.X() &&
                _y == other.Y());
    }

    bool Position::operator!=(Position const& other)
    {
        return (!Position::operator==(other));
    }

    float Position::X() const
    { return _x; }

    void Position::X(float _x)
    { Position::_x = _x; }

    float Position::Y() const
    { return _y; }

    void Position::Y(float _y)
    { Position::_y = _y; }

    Position::Position(Position const& o)
    {
        _x = o.X();
        _y = o.Y();
    }

	Position::Position(Position&& other) :

		_x(std::move(other._x)), _y(std::move(other._x)) //caca
	{
	}

	//Position::Position(Position&& other) : Position(other)
	//{
	//	std::swap(*this, other);
	//}


    Position& Position::operator=(Position other)
    {
        //std::swap(*this, other);
		this->_x = other.X();
		this->_y = other.Y();

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

    Rotation::Rotation(Rotation&& other) : _angle(std::move(other._angle))
    {
    }

    float Rotation::getAngle() const
    {
        return _angle;
    }

    void Rotation::setAngle(float _angle)
    {
        Rotation::_angle = _angle;
    }

    Rotation& Rotation::operator=(Rotation other)
    {
        //std::swap(*this, other);
		this->_angle = other.getAngle();

        return (*this);
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

        ss << "(" << _x << ", " << _y << ")";

        return (ss.str());
    }

    std::string Rotation::toString()
    {
        std::stringstream ss;

        ss << _angle;

        return (ss.str());
    }
}