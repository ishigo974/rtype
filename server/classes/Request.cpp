#include "Request.hpp"
#include "NotImplemented.hpp"

namespace RType
{
    /*
    ** Static variables
    */
    const uint16_t                  Request::unsetCode      = 0;
    const size_t                    Request::variableSize   = 0;
    const size_t                    Request::headerSize     = sizeof(uint16_t) +
                                                              sizeof(uint32_t);
    const Request::LobbyReqMap      Request::lobbyRequests  = {
        { LR_LISTROOMS,     {} },
        { LR_CREATEROOM,    { "room_name" } },
        { LR_JOINROOM,      { "room_id" } },
        { LR_READY,         { "username" } },
        { LR_NOTREADY,      {} },
        { LR_USERNAME,      {} }
    };
    const Request::DataSizeMap      Request::dataSizes  = {
        { "size",       sizeof(uint32_t) },
        { "room_name",  Request::variableSize },
        { "room_id",    sizeof(uint32_t) },
        { "username",   Request::variableSize }
    };

    /*
    ** Constructor/Destructor
    */
    Request::Request() : _protocol(PROTOCOL_UNSET), _code(unsetCode), _size(0)
    {
    }

    Request::Request(Protocol protocol, Buffer const& raw) :
        _protocol(protocol), _code(unsetCode), _size(0)
    {
        parse(raw);
    }

    Request::~Request()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    Request::Request(Request const& other) :
        _code(other._code), _data(other._data)
    {
    }

    Request&        Request::operator=(Request const& other)
    {
        if (this != &other)
        {
            _code = other._code;
            _data = other._data;
        }
        return *this;
    }

    /*
    ** Public member functions
    */
    Request::Protocol   Request::getProtocol() const
    {
        return _protocol;
    }

    uint16_t            Request::getCode() const
    {
        return _code;
    }

    size_t              Request::size() const
    {
        return _size;
    }

    /*
    ** Protected member function
    */
    void            Request::parse(Buffer const& raw)
    {
        size_t      dataSize;

        if (raw.size() < headerSize)
            throw std::runtime_error("incomplete request"); // TODO
        _code = raw.get<uint16_t>();
        dataSize = raw.get<uint32_t>();
        if (raw.size() - headerSize < dataSize)
            throw std::runtime_error("incomplete request"); // TODO
        if (_protocol == PROTOCOL_LOBBY)
            parseLobby(raw);
        else if (_protocol == PROTOCOL_INGAME)
            parseInGame(raw);
    }

    void            Request::parseLobby(Buffer const& raw)
    {
        Buffer                          tmp = raw;
        size_t                          left = raw.size() - headerSize;
        LobbyReqMap::const_iterator     it =
            lobbyRequests.find(static_cast<LobbyRequest>(_code));

        tmp.consume(headerSize);
        if (it == lobbyRequests.end())
            throw Exception::NotImplemented("Request '" + std::to_string(_code)
                + "' does not exists or is not implemented");
        for (std::string const& arg: it->second)
        {
            auto    it = dataSizes.find(arg);
            size_t  size;
            Buffer  res;

            if (it == dataSizes.end())
                throw Exception::NotImplemented("Unknown data size: " + arg);
            if (it->second == variableSize)
            {
                size = tmp.get<uint32_t>();
                tmp.consume(sizeof(uint32_t));
                left -= sizeof(uint32_t);
            }
            else
                size = it->second;
            if (size > left)
                throw std::runtime_error("invalid request (size)"); // TODO
            if (size > tmp.size())
                throw std::runtime_error("incomplete request"); // TODO
            res.setData(tmp.data(), size);
            tmp.consume(size);
            _data.insert(std::make_pair(it->first, res));
            left -= size;
        }
    }

    void            Request::parseInGame(Buffer const& /*raw*/)
    {
        // TODO
    }
}
