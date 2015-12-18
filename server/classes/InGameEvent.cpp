#include "InGameEvent.hpp"

namespace RType
{
    /*
    ** Static variables
    */
    const InGameEvent::EventMap InGameEvent::inGameEvents   =
    {
        { InGameEvent::SE_PLAYERUP,     { "player_id", "time"              } },
        { InGameEvent::SE_PLAYERDOWN,   { "player_id", "time"              } },
        { InGameEvent::SE_PLAYERLEFT,   { "player_id", "time"              } },
        { InGameEvent::SE_PLAYERRIGHT,  { "player_id", "time"              } },
        { InGameEvent::SE_SHOTSTART,    { "player_id", "shot_type", "time" } },
        { InGameEvent::SE_SHOTSTOP,     { "player_id", "time"              } },
        { InGameEvent::SE_MOBSPAWNED,   { "mob_id", "x", "y", "time"       } },
        { InGameEvent::SE_INPUTERROR,   { "time"                           } },
        { InGameEvent::SE_PLYRDISCONN,  {} },
        { InGameEvent::CL_PLAYERUP,     { "time" } },
        { InGameEvent::CL_PLAYERDOWN,   { "time" } },
        { InGameEvent::CL_PLAYERLEFT,   { "time" } },
        { InGameEvent::CL_PLAYERRIGHT,  { "time" } },
        { InGameEvent::CL_SHOTSTART,    { "shot_type", "time" } },
        { InGameEvent::CL_SHOTSTOP,     { "time" } },
        { InGameEvent::CL_DISCONNECT,   {} }
    };

    /*
    ** Constructors/Destructor
    */
    InGameEvent::InGameEvent(uint16_t code) : ABasePacket(code)
    {
    }

    InGameEvent::~InGameEvent()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    InGameEvent::InGameEvent(InGameEvent const& other) :
        ABasePacket(other), _id(other._id)
    {
    }

    InGameEvent&      InGameEvent::operator=(InGameEvent const& other)
    {
        if (this != &other)
        {
            ABasePacket::operator=(other);
            _id = other._id;
        }
        return *this;
    }

    /*
    ** Public member functions
    */
    void        InGameEvent::parse(Buffer const& /*raw*/)
    {
    }

    uint32_t    InGameEvent::getId() const
    {
        return _id;
    }
}
