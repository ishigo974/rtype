//
// Created by naliwe on 23/11/15.
//

#ifndef RTYPE_GAMEOBJECT_HPP_
# define RTYPE_GAMEOBJECT_HPP_

# include "Object.hpp"

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

    virtual std::string toString() override;

    int  getLayer() const;
    void setLayer(unsigned int _layer);

protected:
    void swap(GameObject& first, GameObject& second);

protected:
    int _layer;
};


#endif /* !RTYPE_GAMEOBJECT_HPP_ */
