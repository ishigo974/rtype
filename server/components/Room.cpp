#include <algorithm>
#include <string>
#include "Room.hpp"
#include "Player.hpp"
#include "ComponentsMasks.hpp"
#include "ValueError.hpp"
#include "EntityManager.hpp"

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
        void        Room::update()
        {
            auto it = _players.begin();

            while (it != _players.end())
            {
                try {
                    ECS::EntityManager::getInstance()
                        .get(it->second.first->getId());
                    ++it;
                } catch (Exception::ValueError const&) {
                    _players.erase(it);
                    it = _players.begin();
                }
            }
        }

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

        bool        Room::removePlayer(ECS::Entity& player)
        {
            auto it = std::find_if(_players.begin(), _players.end(),
                [&player](std::pair<unsigned int, PlayerEntry> const& entry)
                { return entry.second.first->getId() == player.getId(); });

            if (it == _players.end())
                return false;
            _players.erase(it);
            return true;
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

        void                    Room::clear()
        {
            _name.clear();
            _players.clear();
        }

        std::string             Room::getName() const
        {
            return "Room";
        }

        std::string             Room::toString() const
        {
            return  std::string("Component::Room {")
                    + std::string("\n\t_name: ") + _name
                    + std::string("\n\tnb players: ") + std::to_string(_players.size())
                    + std::string("\n}\n");
        }

        ECS::ComponentMask      Room::getMask() const
        {
            return Component::MASK_ROOM;
        }

        ECS::IComponent*        Room::clone() const
        {
            return new Room(*this);
        }

        unsigned int            Room::size() const
        {
            return _players.size();
        }

        std::string             Room::getPlayersNames() const
        {
            std::string         res;

            for (auto& player: _players)
            {
                Component::Player*  infos = player.second.first
                    ->getComponent<Component::Player>(Component::MASK_PLAYER);

                if (infos == nullptr)
                    res += "?";
                else
                    res +=  std::string("(") + std::to_string(player.first) +
                            std::string(")") + infos->getUsername();
                res += " ;";
            }
            return res;
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
