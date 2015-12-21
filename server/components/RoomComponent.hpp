#ifndef ROOMCOMPONENT_HPP_
# define ROOMCOMPONENT_HPP_

# include <unordered_map>
# include <vector>
# include <string>
# include "Entity.hpp"
# include "IBehaviour.hpp"
# include "ComponentMask.hpp"
# include "Buffer.hpp"
# include "PositionComponent.hpp"

namespace RType
{
    namespace Component
    {
        class Room : public ECS::IBehaviour
        {
        public:
            typedef std::pair<ECS::Entity*, bool>                   PlayerEntry;
            typedef std::unordered_map<unsigned int, PlayerEntry>   PlayersMap;
            typedef std::unordered_map<unsigned int,
                                        Component::Position>        PlayerPos; // TODO MOVE

        public:
            Room();
            virtual ~Room();

        public:
            Room(Room const& other);
            Room&                       operator=(Room const& other);

        public:
            bool                        addPlayer(ECS::Entity& player);
            bool                        removePlayer(unsigned int id);
            bool                        removePlayer(ECS::Entity& player);
            bool                        setPlayerReadiness(ECS::Entity& player,
                                                           bool isReady);
            void                        setName(std::string const& name);
            void                        broadcastTCP(Buffer const& buffer,
                                          ECS::Entity const* except = nullptr);
            void                        broadcastUDP(Buffer const& buffer,
                                          ECS::Entity const* except = nullptr);
            bool                        allReady() const;
            void                        setIsPlaying(bool isPlaying);

        public:
            std::string const&          getRoomName() const;
            ECS::Entity*                getPlayer(unsigned int id) const;
            unsigned int                getPlayerId(ECS::Entity& entity) const;
            std::string                 getPlayersNames() const;
            unsigned int                size() const;
            PlayersMap const&           getPlayersMap() const;
            bool                        isPlaying() const;
            PlayersMap::const_iterator  begin() const;
            PlayersMap::const_iterator  end() const;

        public:
            virtual void                update();
            virtual void                clear();
            virtual ECS::ComponentMask  getMask() const;
            virtual std::string         getName() const;
            virtual std::string         toString() const;
            virtual ECS::IComponent*    clone() const;

        protected:
            unsigned int                getAvailableId() const;

        public:
            static const unsigned int       nbMaxPlayers;
            static const ECS::ComponentMask mask;
            static const PlayerPos          defaultPositions;

        protected:
            std::string                 _name;
            PlayersMap                  _players;
            bool                        _isPlaying;
        };
    }
}

#endif /* !ROOMCOMPONENT_HPP_ */
