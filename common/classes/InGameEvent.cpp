#include "IncompleteRequest.hpp"
#include "NotImplemented.hpp"
#include "InGameEvent.hpp"

namespace RType
{
    /*
    ** Static variables
    */
    const size_t                InGameEvent::headerSize = sizeof(uint32_t) +
                                                          sizeof(uint16_t) +
                                                          sizeof(uint32_t);
    const InGameEvent::EventMap     InGameEvent::inGameEvents =
    {
        { InGameEvent::SE_PLAYERUP,     { "player_id", "time"               } },
        { InGameEvent::SE_PLAYERDOWN,   { "player_id", "time"               } },
        { InGameEvent::SE_PLAYERLEFT,   { "player_id", "time"               } },
        { InGameEvent::SE_PLAYERRIGHT,  { "player_id", "time"               } },
        { InGameEvent::SE_SHOT,         { "player_id", "shot_type", "time"  } },
        { InGameEvent::SE_MOBSPAWNED,   { "mobtype_id", "mob_id", "x", "y",
                                          "time"                            } },
        { InGameEvent::SE_MOBMOVED,     { "mob_id", "x", "y", "time"        } },
        { InGameEvent::SE_INPUTERROR,   { "time"                            } },
        { InGameEvent::SE_PLYRDISCONN,  {                                   } },
        { InGameEvent::CL_PLAYERUP,     { "time"                            } },
        { InGameEvent::CL_PLAYERDOWN,   { "time"                            } },
        { InGameEvent::CL_PLAYERLEFT,   { "time"                            } },
        { InGameEvent::CL_PLAYERRIGHT,  { "time"                            } },
        { InGameEvent::CL_SHOT,         { "shot_type", "time"               } },
        { InGameEvent::CL_DISCONNECT,   {                                   } }
    };
    const InGameEvent::DataSizeMap  InGameEvent::dataSizes    = {
        { "size",           sizeof(uint32_t) },
        { "player_id",      sizeof(uint8_t)  },
        { "time",           sizeof(uint64_t) },
        { "shot_type",      sizeof(uint8_t)  },
        { "mobtype_id",     sizeof(uint8_t)  },
        { "mob_id",         sizeof(uint64_t) },
        { "x",              sizeof(uint32_t) },
        { "y",              sizeof(uint32_t) }
    };

    /*
    ** Constructors/Destructor
    */
    InGameEvent::InGameEvent(uint16_t code) : ABasePacket(code), _id(0)
    {
    }

    InGameEvent::InGameEvent(Buffer const& raw) : ABasePacket(), _id(0)
    {
        parse(raw);
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

    InGameEvent& InGameEvent::operator=(InGameEvent const& other)
    {
        if (this != &other)
        {
            ABasePacket::operator=(other);
            _id = other._id;
        }
        return *this;
    }

    /*
    ** Overloaded operators
    */
    bool        InGameEvent::operator<(InGameEvent const& other) const
    {
        return _id < other._id;
    }

    bool        InGameEvent::operator>(InGameEvent const& other) const
    {
        return _id > other._id;
    }

    bool        InGameEvent::operator<=(InGameEvent const& other) const
    {
        return _id <= other._id;
    }

    bool        InGameEvent::operator>=(InGameEvent const& other) const
    {
        return _id >= other._id;
    }

    bool        InGameEvent::operator==(InGameEvent const& other) const
    {
        return ABasePacket::operator==(other) && _id == other._id;
    }

    /*
    ** Public member functions
    */
    void        InGameEvent::parse(Buffer const& raw)
    {
        size_t dataSize;

        clear();
        if (raw.size() < headerSize)
            throw Exception::IncompleteRequest("Buffer can't contain a \
                                                request header");
        _id      = raw.get<uint32_t>();
        _code    = raw.get<uint16_t>(sizeof(uint32_t));
        dataSize = raw.get<uint32_t>(sizeof(uint32_t) + sizeof(uint16_t));
        if (raw.size() - headerSize < dataSize)
            throw Exception::IncompleteRequest("Buffer can't contain \
                                                request's data");
        parseData(raw);
    }

    void        InGameEvent::parseData(Buffer const& raw)
    {
        Buffer                   tmp = raw;
        EventMap::const_iterator it  =
            inGameEvents.find(static_cast<Code>(_code));

        tmp.consume(headerSize);
        if (it == inGameEvents.end())
            throw Exception::NotImplemented("Request '" + std::to_string(_code)
                                + "' does not exists or is not implemented");
        for (std::string const& arg: it->second)
        {
            auto   it = dataSizes.find(arg);
            Buffer res;

            if (it == dataSizes.end())
                throw Exception::NotImplemented("Unknown data size: " + arg);
            if (it->second > tmp.size())
                throw Exception::IncompleteRequest("Buffer can't "
                                                    "contain argument");
            res.setData(tmp.data(), it->second);
            tmp.consume(it->second);
            _data.insert(std::make_pair(it->first, res));
        }
    }

    Buffer      InGameEvent::toBuffer() const
    {
        Buffer res;
        Buffer data;
        auto   it = inGameEvents.find(static_cast<Code>(_code));

        if (it == inGameEvents.end())
            throw Exception::IncompleteRequest("Code " + std::to_string(_code) +
                                               " does not match any requests");
        res.append<uint32_t>(_id);
        res.append<uint16_t>(_code);
        for (auto& arg: it->second)
            data.append<Buffer>(_data.at(arg));
        res.append<uint32_t>(data.size());
        res.append(data);
        return res;
    }

    void        InGameEvent::clear()
    {
        ABasePacket::clear();
        _id = 0;
    }

    void        InGameEvent::setId(uint32_t id)
    {
        _id = id;
    }

    uint32_t    InGameEvent::getId() const
    {
        return _id;
    }
}
