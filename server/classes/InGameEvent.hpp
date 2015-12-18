#ifndef INGAMEEVENT_HPP_
# define INGAMEEVENT_HPP_

# include <string>
# include "Buffer.hpp"
# include "ABasePacket.hpp"

namespace RType
{
    class InGameEvent : public ABasePacket
    {
    public:
        enum Code
        {
        };

    public:
        InGameEvent(uint16_t code = 0);
        virtual ~InGameEvent();

    public:
        InGameEvent(InGameEvent const& other);
        InGameEvent&    operator=(InGameEvent const& other);

    public:
        virtual void    parse(Buffer const& raw);

    public:
        uint32_t        getId() const;

    protected:
        uint32_t        _id;
    };
}

#endif /* !INGAMEEVENT_HPP_ */
