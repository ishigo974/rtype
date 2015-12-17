#include "InGameEvent.hpp"

namespace RType
{
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
