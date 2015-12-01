//
// Created by fourdr_b on 27/11/15.
//

#ifndef RTYPE_UTILS_HPP
# define RTYPE_UTILS_HPP

# include <algorithm>

namespace cu
{
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
        void  X(float _x);

        float Y() const;
        void  Y(float _y);

        std::string toString();

        void swap(Position &other);

    private:
        float _x;
        float _y;
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

        void swap(Rotation &other);

    private:
        float _angle;
    };
}

#endif //RTYPE_UTILS_HPP
