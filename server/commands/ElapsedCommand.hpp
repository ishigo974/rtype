#ifndef ELAPSEDCOMMAND_HPP_
# define ELAPSEDCOMMAND_HPP_

# include "EventCommand.hpp"

namespace RType
{
    namespace Command
    {
        class Elapsed : public Command::Event
        {
        public:
            Elapsed();
            virtual ~Elapsed();

        public:
            Elapsed(Elapsed const& other);
            Elapsed&                operator=(Elapsed const& other);

        public:
            virtual void            initFromEvent(InGameEvent const& request);
            virtual Event*          clone() const;
            virtual void            execute();
            virtual void            undo();
            virtual std::string     getName() const;

        protected:
            double                  _elapsedTime;
        };
    }
}

#endif /* !ELAPSEDCOMMAND_HPP_ */
