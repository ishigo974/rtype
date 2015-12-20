#include <algorithm>
#include <string>
#include <iostream>
#include "RoomComponent.hpp"
#include "PlayerComponent.hpp"
#include "ComponentsMasks.hpp"
#include "ValueError.hpp"
#include "EntityManager.hpp"
#include "NetworkTCP.hpp"
#include "NetworkUDP.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const unsigned int          Room::nbMaxPlayers      = 4;
        const ECS::ComponentMask    Room::mask              = MASK_ROOM;
        const Room::PlayerPos       Room::defaultPositions  =
        {
            { 1, Component::Position(20, 100) },
            { 2, Component::Position(20, 150) },
            { 3, Component::Position(20, 200) },
            { 4, Component::Position(20, 250) }
        };

        /*
        ** Constructor/Destructor
        */
        Room::Room() : _isPlaying(false)
        {
        }

        Room::~Room()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Room::Room(Room const& other) :
            _name(other._name), _players(other._players),
            _isPlaying(other._isPlaying)
        {
        }

        Room&       Room::operator=(Room const& other)
        {
            if (this != &other)
            {
                _name = other._name;
                _players = other._players;
                _isPlaying = other._isPlaying;
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

        void        Room::broadcastTCP(Buffer const& buffer,
                                       ECS::Entity const* except)
        {
            for (auto& entry: _players)
            {
                Component::NetworkTCP*  network = entry.second.first
                    ->getComponent<Component::NetworkTCP>();

                if (network == nullptr)
                    throw std::runtime_error("Player entity is missing his "
                                             "NetworkTCP component"); // TODO except
                if (except == nullptr || except != entry.second.first)
                    network->send(buffer);
            }
        }

        void        Room::broadcastUDP(Buffer const& buffer,
                                       ECS::Entity const* except)
        {
            for (auto& entry: _players)
            {
                Component::NetworkUDP*  network = entry.second.first
                    ->getComponent<Component::NetworkUDP>();

                if (network == nullptr)
                    throw std::runtime_error("Player entity is missing his "
                                             "NetworkUDP component"); // TODO except
                if (except == nullptr || except != entry.second.first)
                    network->send(buffer);
            }
        }

        unsigned int    Room::getPlayerId(ECS::Entity& player) const
        {
            auto it = std::find_if(_players.begin(), _players.end(),
                [&player](std::pair<unsigned int, PlayerEntry> const& entry)
                { return entry.second.first->getId() == player.getId(); });

            if (it == _players.end())
                throw Exception::ValueError("Player not found");
            return it->first;
        }

        bool        Room::setPlayerReadiness(ECS::Entity& player, bool isReady)
        {
            auto it = std::find_if(_players.begin(), _players.end(),
                [&player](std::pair<unsigned int, PlayerEntry> const& entry)
                { return entry.second.first->getId() == player.getId(); });

            if (it == _players.end())
                return false;
            it->second.second = isReady;
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
            _isPlaying = false;
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
            return mask;
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

            if (_players.empty())
                return "";
            for (auto& player: _players)
            {
                Component::Player*  infos = player.second.first
                    ->getComponent<Component::Player>();

                if (infos == nullptr)
                    res += "?";
                else
                    res +=  std::string("(") + std::to_string(player.first) +
                            std::string(":") +
                            (player.second.second ? "r" : "n") +
                            std::string(")") + infos->getUsername();
                res += ", ";
            }
            return res.substr(0, res.size() - 2);
        }

        Room::PlayersMap const&         Room::getPlayersMap() const
        {
            return _players;
        }

        bool                            Room::allReady() const
        {
            return std::find_if(_players.begin(), _players.end(),
                   [](std::pair<unsigned int, PlayerEntry> const& entry)
                   { return entry.second.second == false; }) == _players.end();
        }

        void                    Room::setIsPlaying(bool isPlaying)
        {
            _isPlaying = isPlaying;
        }

        bool                    Room::isPlaying() const
        {
            return _isPlaying;
        }

        Room::PlayersMap::const_iterator  Room::begin() const
        {
            return _players.begin();
        }

        Room::PlayersMap::const_iterator  Room::end() const
        {
            return _players.end();
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
