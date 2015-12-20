#ifndef RTYPE_GAMEOBJECT_HPP_
# define RTYPE_GAMEOBJECT_HPP_

# include <vector>
# include <memory>
# include <iostream>
# include <algorithm>
# include "Object.hpp"
# include "Component.hpp"
# include "Transform.hpp"
# include "SpriteRenderer.hpp"

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

    virtual Transform     & transform() const;
    virtual SpriteRenderer& renderer() const;

    void swap(GameObject& other);

public:
    virtual bool findMask(RTypes::my_uint16_t mask);
    void         addComponent(Component *const newComp);

    virtual std::string toString();
    int                 getLayer() const;
    void                setLayer(unsigned int _layer);

public:
    template<class T, typename = std::enable_if<std::is_base_of<Component, T>::value> >
    T *getComponent() const
    {
        auto selected = std::find_if(_components.begin(), _components.end(), [](auto& e)
        {
            return (e->getMask() == T::Mask);
        });

        return ((selected == _components.end()) ? nullptr : static_cast<T *>(*selected));
    };

    template<class ...Args>
    void broadcastMessage(Args... args)
    {
        for (auto& e : _components)
        {
            e->handleMessage(args...);
        }
    }

    template<class ...Args>
    void sendMessage(Args... args)
    {
        for (auto& e : _components)
        {
            if (e->handleMessage(args...))
                return;
        }
    }

protected:
    int                      _layer;
    std::vector<Component *> _components;
};


#endif /* !RTYPE_GAMEOBJECT_HPP_ */
