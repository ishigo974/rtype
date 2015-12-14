#ifndef ROOMCOMPONENT_HPP_
# define ROOMCOMPONENT_HPP_

# include <unordered_map>
# include <vector>
# include <string>
# include "Entity.hpp"
# include "IBehaviour.hpp"
# include "ComponentMask.hpp"
# include "Buffer.hpp"

namespace RType
{
    namespace Component
    {
        class Room : public ECS::IBehaviour
        {
        public:
            typedef std::pair<ECS::Entity*, bool>                   PlayerEntry;
            typedef std::unordered_map<unsigned int, PlayerEntry>   PlayersMap;

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
            void                        broadcast(Buffer const& buffer,
                                          ECS::Entity const* except = nullptr);

        public:
            std::string const&          getRoomName() const;
            ECS::Entity*                getPlayer(unsigned int id) const;
            unsigned int                getPlayerId(ECS::Entity& entity) const;
            std::string                 getPlayersNames() const;
            unsigned int                size() const;

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
            static const unsigned int   nbMaxPlayers;

        protected:
            std::string                 _name;
            PlayersMap                  _players;
        };
    }
}

#endif /* !ROOMCOMPONENT_HPP_ */
