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
    Component(unsigned int _id, std::string const& _name, RTypes::my_uint16_t _mask);
    Component(Component const& other);
    Component(Component&& other);
    virtual Component& operator=(Component other);
    virtual ~Component();

    virtual bool operator==(Component const& other);
    virtual bool operator!=(Component const& other);

    RTypes::my_uint16_t getMask() const;
    void                setMask(RTypes::my_uint16_t _mask);

    virtual std::string toString();

protected:
    virtual void swap(Component& first, Component& second);

private:
    RTypes::my_uint16_t _mask;
};

#endif /* !RTYPE_COMPONENT_HPP_ */
