#ifndef GAMECOMPONENT_HPP_
# define GAMECOMPONENT_HPP_

# include <string>
# include <vector>
# include "ComponentMask.hpp"
# include "IBehaviour.hpp"
# include "HRChrono.hpp"
# include "MapParser.hpp"
# include "RoomComponent.hpp"
# include "GameClock.hpp"

namespace RType
{
    namespace Component
    {
        class Game : public ECS::IBehaviour
        {
        public:
            Game();
            virtual ~Game();

        public:
            Game(Game const& other);
            Game&                       operator=(Game const& other);

        public:
            Map::Parser::Map&           retrieveMap();
            void                        start(Map::Parser::Map const& map);
            Time::HRChrono const&       getChrono() const;
            double                      getLastElapsed() const;

        public:
            virtual void                update();

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask     mask;

        protected:
            Time::HRChrono      _chrono;
            Component::Room*    _room;
            Map::Parser::Map    _map;
            Time::GameClock     _clock;
            double              _lag;
        };
    }
}

#endif /* !GAMECOMPONENT_HPP_ */
