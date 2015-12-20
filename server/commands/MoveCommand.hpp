#ifndef MOVECOMMAND_HPP_
# define MOVECOMMAND_HPP_

# include "EventCommand.hpp"

namespace RType
{
    namespace Command
    {
        class Move : public Command::Event
        {
        public:
            enum Direction
            {
                NONE,
                UP,
                DOWN,
                LEFT,
                RIGHT
            };

        public:
            typedef std::unordered_map<Direction,
                                       InGameEvent::Code,
                                       std::hash<int> >   DirCodeMatch;

        public:
            Move();
            virtual ~Move();

        public:
            Move(Move const& other);
            Move&                   operator=(Move const& other);

        public:
            virtual void            initFromEvent(InGameEvent const& request);
            virtual Event*          clone() const;
            virtual void            execute();
            virtual void            undo();
            virtual std::string     getName() const;

        public:
            static const DirCodeMatch  dirCodeMatches;

        protected:
            Direction           _direction;
            uint32_t            _time;
        };
    }
}

#endif /* !MOVECOMMAND_HPP_ */
