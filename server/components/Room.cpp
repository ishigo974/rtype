#include <algorithm>
#include "Room.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const unsigned int      Room::nbMaxPlayers  = 4;

        /*
        ** Constructor/Destructor
        */
        Room::Room()
        {
        }

        Room::~Room()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Room::Room(Room const& other) :
            _name(other._name), _players(other._players)
        {
        }

        Room&       Room::operator=(Room const& other)
        {
            if (this != &other)
            {
                _name = other._name;
                _players = other._players;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        bool        Room::addPlayer(ECS::Entity& player)
        {
            unsigned int    id = getAvailableId();

            if (id == 0 || _players.size() >= nbMaxPlayers)
                return false;
            _players.insert(std::make_pair(id, std::make_pair(&player, false)));
            return true;
        }

        bool        Room::removePlayer(unsigned int id)
        {
            return _players.erase(id) > 0;
        }

        void        Room::setName(std::string const& name)
        {
            _name = name;
        }

        std::string const&      Room::getRoomName() const
        {
            return _name;
        }

        ECS::Entity*            Room::getPlayer(unsigned int id) const
        {
            auto    it = _players.find(id);

            if (it == _players.end())
                return nullptr;
            return it->second.first;
        }

        std::string             Room::getName() const
        {
            return "Room";
        }

        /*
        ** Protected member functions
        */
        unsigned int            Room::getAvailableId() const
        {
            static const std::vector<unsigned int>      ids = { 1, 2, 3, 4 };

            for (unsigned int id: ids)
            {
                if (_players.find(id) == _players.end())
                    return id;
            }
            return 0;
        }
    }
}
