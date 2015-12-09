#ifndef ROOM_HPP_
# define ROOM_HPP_

# include <unordered_map>
# include <vector>
# include <string>
# include "Entity.hpp"
# include "IComponent.hpp"

namespace RType
{
    namespace Component
    {
        class Room : public ECS::IComponent
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
            void                        setName(std::string const& name);

        public:
            std::string const&          getRoomName() const;
            ECS::Entity*                getPlayer(unsigned int id) const;

        public:
            virtual std::string         getName() const;

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

#endif /* !ROOM_HPP_ */
