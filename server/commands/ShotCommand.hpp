#ifndef SHOTCOMMAND_HPP_
# define SHOTCOMMAND_HPP_

# include "EventCommand.hpp"
# include "ShotComponent.hpp"

namespace RType
{
    namespace Command
    {
        class Shot : public Command::Event
        {
        public:
            Shot();
            virtual ~Shot();

        public:
            Shot(Shot const& other);
            Shot&                   operator=(Shot const& other);

        public:
            virtual void            initFromEvent(InGameEvent const& request);
            virtual Event*          clone() const;
            virtual void            execute();
            virtual void            undo();
            virtual std::string     getName() const;

        protected:
            bool                    _isFiring;
            Component::Shot::Type   _type;
            uint32_t                _time;
        };
    }
}

#endif /* !SHOTCOMMAND_HPP_ */
