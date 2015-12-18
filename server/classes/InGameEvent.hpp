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
        /*
        ** Server to client codes are prefixed by SE_
        ** Client to server codes are prefixed by CL_
        */
        enum Code
        {
            SE_PLAYERUP     = 301,
            SE_PLAYERDOWN   = 302,
            SE_PLAYERLEFT   = 303,
            SE_PLAYERRIGHT  = 304,
            SE_SHOTSTART    = 305,
            SE_SHOTSTOP     = 306,
            SE_MOBSPAWNED   = 307,
            SE_INPUTERROR   = 501,
            SE_PLYRDISCONN  = 502,
            CL_PLAYERUP     = 201,
            CL_PLAYERDOWN   = 202,
            CL_PLAYERLEFT   = 203,
            CL_PLAYERRIGHT  = 204,
            CL_SHOTSTART    = 205,
            CL_SHOTSTOP     = 206,
            CL_DISCONNECT   = 503
        };

    public:
        typedef std::vector<std::string>                    DataArgs;
        typedef std::unordered_map<Code, DataArgs,
                                    std::hash<uint16_t> >   EventMap;

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

    public:
        static const EventMap   inGameEvents;

    protected:
        uint32_t        _id;
    };
}

#endif /* !INGAMEEVENT_HPP_ */
