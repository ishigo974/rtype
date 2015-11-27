#ifndef RTYPE_GAMEOBJECT_HPP_
# define RTYPE_GAMEOBJECT_HPP_

# include "Object.hpp"

class GameObject : public Object
{

public:

    GameObject();
    GameObject(unsigned int _id, std::string const& _name, unsigned int _layer);

    GameObject(GameObject const& other);
    GameObject(GameObject&& other);
    GameObject& operator=(GameObject other);

    virtual ~GameObject();

    virtual bool operator==(GameObject const& other);
    virtual bool operator!=(GameObject const& other);

    virtual std::string const& toString() override;

    unsigned int getLayer() const;
    void setLayer(unsigned int _layer);

private:
    void swap(GameObject& first, GameObject& second) const;

protected:
    unsigned int _layer;
};


#endif /* !RTYPE_GAMEOBJECT_HPP_ */
