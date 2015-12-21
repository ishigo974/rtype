#ifndef RTYPE_COMPONENT_HPP_
# define RTYPE_COMPONENT_HPP_

# include "Object.hpp"
# include "RTypes.hpp"
# include "REnums.hpp"

class Collider;

class Component : public Object
{
public:
    static RTypes::my_uint16_t const Mask = ComponentMask::DefaultMask;

public:
    Component();
    Component(unsigned int _id, std::string const& _name);
    Component(Component const& other);
    Component(Component&& other);
    virtual Component& operator=(Component other);
    virtual ~Component();

    virtual bool operator==(Component const& other);
    virtual bool operator!=(Component const& other);

public:
    virtual bool handleMessage(Collider *o);

public:
    void swap(Component& other);

    virtual RTypes::my_uint16_t getMask() const;

    virtual std::string toString() const;

    virtual Object *parent() const;
};

static const Component ErrorComponent = Component(0, "Error");

#endif /* !RTYPE_COMPONENT_HPP_ */
