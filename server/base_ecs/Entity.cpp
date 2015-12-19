#include <iostream>
#include <sstream>
#include "Entity.hpp"
#include "IBehaviour.hpp"

namespace ECS
{
    /*
    ** Constructors/Destructor
    */
    Entity::Entity() : _id(0), _mask(0)
    {
    }

    Entity::Entity(unsigned int id) : _id(id), _mask(0)
    {
    }

    Entity::~Entity()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    Entity::Entity(Entity const& other) :
    _id(other._id), _mask(other._mask)
    {
        for (auto&& i : other._components)
            _components[i.first] = std::unique_ptr<IComponent>(i.second->clone());
    }

    Entity&         Entity::operator=(Entity const& other)
    {
        if (this != &other)
        {
            _id = other._id;
            _mask = other._mask;
            _components.clear();
            for (auto&& i : other._components)
                _components[i.first] = std::unique_ptr<IComponent>(i.second->clone());
        }
        return *this;
    }

    /*
    ** Public member functions
    */
    void            Entity::clear()
    {
        for (auto&& i : _components)
            i.second->clear();
    }

    void            Entity::addComponent(std::unique_ptr<IComponent> component)
    {
        _mask |= component->getMask();
        _components[component->getMask()] = std::move(component);
    }

    bool            Entity::removeComponent(ComponentMask mask)
    {
        if (_components.erase(mask) > 0)
        {
            _mask &= mask;
            return true;
        }
        return false;
    }

    void              Entity::update()
    {
        for (auto& c: _components)
        {
            IBehaviour*   b = dynamic_cast<IBehaviour*>(c.second.get());

            if (b != nullptr)
            b->update();
        }
    }

    unsigned int    Entity::getId() const
    {
        return _id;
    }

    ComponentMask   Entity::getComponentMask() const
    {
        return _mask;
    }

    std::string     Entity::toString() const
    {
        std::string res;

        res = "Entity {";
        res += "\n\t _id " + std::to_string(_id);
        res += "\n\t _mask " + std::to_string(_mask);
        res += "\n\t _components";
        for (auto&& i : _components)
            res += std::string(" ") + i.second->getName();
        res += "\n";
        return res;
    }
}
