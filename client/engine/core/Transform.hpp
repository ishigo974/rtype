//
// Created by fourdr_b on 27/11/15.
//

#ifndef RTYPE_TRANSFORM_HPP
#define RTYPE_TRANSFORM_HPP

# include "Component.hpp"
# include "Utils.hpp"

class Transform : public Component
{

public:
    Transform();
    Transform(unsigned int _id);
    Transform(unsigned int _id, cu::Position const& pos);
    Transform(unsigned int _id, std::string const& _name,
              cu::Position const& pos, cu::Scale scale, cu::Rotation rot);

    Transform(Transform const& other);
    Transform(Transform&& other);
    virtual Transform& operator=(Transform other);

    virtual ~Transform();

    virtual bool operator==(Transform const& other);
    virtual bool operator!=(Transform const& other);

    virtual std::string toString();

    void swap(Transform& second);

    cu::Position& getPosition();
    cu::Position const& getPosition() const;
    void setPosition(cu::Position const& _position);

    cu::Scale& getScale();
    cu::Scale const& getScale() const;
    void setScale(cu::Scale const& _scale);

    cu::Rotation& getRotation();
    cu::Rotation const& getRotation() const;
    void setRotation(cu::Rotation const& _rotation);

private:
    cu::Position _position;
    cu::Scale    _scale;
    cu::Rotation _rotation;
};


#endif //RTYPE_TRANSFORM_HPP
