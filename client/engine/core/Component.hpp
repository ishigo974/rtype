//
// Created by naliwe on 23/11/15.
//

#ifndef RTYPE_COMPONENT_HPP_
# define RTYPE_COMPONENT_HPP_

# include "Object.hpp"

class Component : public Object
{
public:
    Component();
    Component(uint _id, std::string const& _name, u_int16_t _mask);
    Component(Component const& other);
    Component(Component&& other);
    Component& operator=(Component other);
    virtual ~Component();

    bool operator==(Component const& other);
    bool operator!=(Component const& other);

    u_int16_t getMask() const;
    void      setMask(u_int16_t _mask);

    virtual std::string toString() override;

protected:
    void swap(Component& first, Component& second);

private:
    u_int16_t _mask;
};

#endif /* !RTYPE_COMPONENT_HPP_ */
