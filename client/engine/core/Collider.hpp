//
// Created by naliwe on 01/12/15.
//

#ifndef RTYPE_COLLIDER_HPP_
# define RTYPE_COLLIDER_HPP_

# include <string>
# include <vector>
# include "Component.hpp"
# include "Utils.hpp"
# include "Rect.hpp"

class Collider : public Component
{
public:
    static const RTypes::my_uint16_t Mask = ComponentMask::ColliderMask;

public:
    Collider();
    Collider(unsigned int _id, std::string const& _name, int width, int height);

    Collider(Collider const& other);
    Collider(Collider&& other);
    virtual Collider& operator=(Collider other);

    virtual ~Collider();

    virtual bool operator==(Collider const& other);
    virtual bool operator!=(Collider const& other);

    void swap(Collider& other);

public:
    virtual void fixedUpdate(double elapsedtime);

    virtual RTypes::my_uint16_t getMask() const;
    virtual std::string         toString() const;

public:
    bool intersects(Collider *o) const;
    bool isEnabled() const;
    bool isTraversable() const;
    void setEnabled(bool e);
    void setRect(gu::Rect<int> const&);

protected:
    gu::Rect<int> _bounds;
    bool          _enabled;
    bool          _traversable;
};


#endif /* !RTYPE_COLLIDER_HPP_ */
