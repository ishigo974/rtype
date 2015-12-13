//
// Created by naliwe on 01/12/15.
//

#ifndef RTYPE_COLLIDER_HPP_
# define RTYPE_COLLIDER_HPP_

# include <string>
# include <vector>
# include "Component.hpp"
# include "Utils.hpp"

class Collider : public Component
{
public:
    static const RTypes::my_uint16_t Mask = ComponentMask::ColliderMask;

public:
    Collider();
    Collider(unsigned int _id, std::string const& _name);

    Collider(Collider const& other);
    Collider(Collider&& other);
    virtual Collider& operator=(Collider other);

    virtual ~Collider();

    virtual bool operator==(Collider const& other);
    virtual bool operator!=(Collider const& other);

    void swap(Collider& other);

    virtual RTypes::my_uint16_t getMask() const;
    virtual std::string         toString();

protected:
    std::vector<cu::Point2D> _bounds;
};


#endif /* !RTYPE_COLLIDER_HPP_ */

