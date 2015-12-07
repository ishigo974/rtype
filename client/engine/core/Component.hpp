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

    virtual void swap(Component &other);

    virtual RTypes::my_uint16_t getMask() const;

    virtual std::string toString();

    static RTypes::my_uint16_t const Mask = 0;
};

static const Component ErrorComponent = Component(0, "Error");

#endif /* !RTYPE_COMPONENT_HPP_ */
