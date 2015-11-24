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
    GameObject(uint _id, std::string const& _name, uint _layer);

    GameObject(GameObject const& other);
    GameObject(GameObject&& other);
    GameObject& operator=(GameObject other);

    virtual ~GameObject();

    virtual bool operator==(GameObject const& other);
    virtual bool operator!=(GameObject const& other);

    virtual std::string const& toString() override;

    uint getLayer() const;
    void setLayer(uint _layer);

private:
    void swap(GameObject& first, GameObject& second);

protected:
    uint _layer;
};


#endif /* !RTYPE_GAMEOBJECT_HPP_ */
