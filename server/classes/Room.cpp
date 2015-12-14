#include "Room.hpp"

namespace RType
{
    Room::Room() : _id(0), _name(""), _nbPlayers(0)
    {
    }

    Room::~Room()
    {
    }


    Room::Room(Room const& other) :
        _id(other._id), _name(other._name), _nbPlayers(other._nbPlayers)
    {
    }

    Room&           Room::operator=(Room const& other)
    {
        if (this != &other)
        {
            _id = other._id;
            _name = other._name;
            _nbPlayers = other._nbPlayers;
        }
        return *this;
    }


    unsigned int    Room::getId() const
    {
        return _id;
    }

    std::string     Room::getName() const
    {
        return _name;
    }

    unsigned int    Room::getNbPlayers() const
    {
        return _nbPlayers;
    }


    void            Room::setId(unsigned int id)
    {
        _id = id;
    }

    void            Room::setName(std::string const& name)
    {
        _name = name;
    }

    void            Room::setNbPlayers(unsigned int nbPlayers)
    {
        _nbPlayers = nbPlayers;
    }
}
