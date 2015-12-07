//
// Created by naliwe on 23/11/15.
//

#ifndef RTYPE_GAMEOBJECT_HPP_
# define RTYPE_GAMEOBJECT_HPP_

# include <vector>
# include <memory>
# include <algorithm>
# include "Object.hpp"
# include "Component.hpp"
# include "Transform.hpp"

# include <iostream>
#include <SpriteRenderer.hpp>

class Component;

class GameObject : public Object
{
public:
    GameObject();
    GameObject(unsigned int _id, std::string const& _name, int _layer);

    GameObject(GameObject const& other);
    GameObject(GameObject&& other);
    GameObject& operator=(GameObject other);

    virtual ~GameObject();

    virtual bool operator==(GameObject const& other);
    virtual bool operator!=(GameObject const& other);

    virtual Transform& transform() const;
    virtual SpriteRenderer& renderer() const;

    virtual std::string toString();

    int  getLayer() const;
    void setLayer(unsigned int _layer);

    virtual unsigned int getMask();

    void addComponent(Component *const newComp);

    template<class T, typename = std::enable_if<std::is_base_of<Component, T>::value> >
    T *getComponent() const
    {
        auto selected = std::find_if(_components.begin(), _components.end(), [](auto& e)
        {
            return (e->getMask() == T::Mask);
        });

        return ((selected == _components.end()) ? nullptr : static_cast<T *>(*selected));
    };

    void swap(GameObject& other);

protected:
    int                      _layer;
    std::vector<Component *> _components;
};


#endif /* !RTYPE_GAMEOBJECT_HPP_ */
