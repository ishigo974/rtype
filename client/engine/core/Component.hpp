//
// Created by naliwe on 23/11/15.
//

#ifndef RTYPE_COMPONENT_HPP_
# define RTYPE_COMPONENT_HPP_

# include "Object.hpp"
# include "RTypes.hpp"

class Component : public Object
{
public:
    Component();
    Component(unsigned int _id, std::string const& _name);
    Component(Component const& other);
    Component(Component&& other);
    virtual Component& operator=(Component other);
    virtual ~Component();

    virtual bool operator==(Component const& other);
    virtual bool operator!=(Component const& other);

    virtual RTypes::my_uint16_t getMask() const;

    virtual std::string toString();

    static RTypes::my_uint16_t const Mask = 0;
};

#endif /* !RTYPE_COMPONENT_HPP_ */
