#include <iostream>
#include <sstream>
#include "Request.hpp"
#include "NotImplemented.hpp"
#include "InvalidRequest.hpp"
#include "IncompleteRequest.hpp"

namespace RType
{
    /*
    ** Static variables
    */
    const uint16_t                  Request::unsetCode    = 0;
    const size_t                    Request::variableSize = 0;
    const size_t                    Request::headerSize   = sizeof(uint16_t) +
                                                            sizeof(uint32_t);
    const Request::LobbyReqMap      Request::lobbyRequests = {
            {CL_LISTROOMS,  {}},
            {CL_CREATEROOM, {"room_name"}},
            {CL_JOINROOM,   {"room_id"}},
            {CL_QUITROOM,   {}},
            {CL_READY,      {}},
            {CL_NOTREADY,   {}},
            {CL_USERNAME,   {"username"}},
            {SE_LISTROOMS,  {"rooms"}},
            {SE_JOINROOM,   {"player_id", "username"}},
            {SE_CLIUSRNM,   {"player_id", "username"}},
            {SE_CLIENTRDY,  {"player_id"}},
            {SE_CLINOTRDY,  {"player_id"}},
            {SE_GAMESTART,  {}},
            {SE_ROOMINFO,   {"player_id", "players"}},
            {SE_QUITROOM,   {"player_id"}},
            {SE_OK,         {}},
            {SE_KO,         {}}
    };
    const Request::DataSizeMap      Request::dataSizes     = {
            {"size",      sizeof(uint32_t)},
            {"room_name", Request::variableSize},
            {"room_id",   sizeof(uint32_t)},
            {"username",  Request::variableSize},
            {"rooms",     Request::variableSize},
            {"player_id", sizeof(uint8_t)},
            {"players",   Request::variableSize}
    };

    /*
    ** Constructor/Destructor
    */
    Request::Request(uint16_t code) : ABasePacket(code)
    {
    }

    Request::Request(Buffer const& raw) : ABasePacket()
    {
        parse(raw);
    }

    Request::~Request()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    Request::Request(Request const& other) : ABasePacket(other)
    {
    }

    Request& Request::operator=(Request const& other)
    {
        if (this != &other)
            ABasePacket::operator=(other);
        return *this;
    }

    /*
    ** Public member functions
    */
    template<>
    Request::RoomsTab   Request::get(std::string const& key) const
    {
        DataMap::const_iterator it = _data.find(key);
        RoomsTab                res;
        Buffer                  buffer;

        if (_code != SE_LISTROOMS)
            throw Exception::ValueError("Trying to retrieve rooms collection");
        if (it == _data.end())
            throw std::runtime_error("no such data: " + key); // TODO
        buffer = it->second;
        while (!buffer.empty())
        {
            Room     room;
            uint32_t size;

            room.id = buffer.get<uint32_t>();
            buffer.consume(sizeof(uint32_t));
            size = buffer.get<uint32_t>();
            buffer.consume(sizeof(uint32_t));
            room.name = buffer.getString(size);
            buffer.consume(size);
            room.nbPlayers = buffer.get<uint8_t>();
            buffer.consume(sizeof(uint8_t));
            res.push_back(room);
        }
        return res;
    }

    template<>
    Request::PlayersTab Request::get(std::string const& key) const
    {
        DataMap::const_iterator it = _data.find(key);
        PlayersTab              players;
        Buffer                  buffer;

        if (_code != SE_ROOMINFO)
            throw Exception::ValueError("Trying to retrieve players infos");
        if (it == _data.end())
            throw std::runtime_error("no such data: " + key); // TODO
        buffer = it->second;
        while (!buffer.empty())
        {
            Player   player;
            uint32_t size;

            player.id = buffer.get<uint8_t>();
            buffer.consume(sizeof(uint8_t));
            size = buffer.get<uint32_t>();
            buffer.consume(sizeof(uint32_t));
            player.username = buffer.getString(size);
            buffer.consume(size);
            player.isReady = (buffer.get<uint8_t>() != 0);
            buffer.consume(sizeof(uint8_t));
            players.push_back(player);
        }
        return players;
    }

    Buffer          Request::toBuffer() const
    {
        Buffer res;
        Buffer data;
        auto   it = lobbyRequests.find(static_cast<Code>(_code));

        if (it == lobbyRequests.end())
            throw Exception::IncompleteRequest("Code " + std::to_string(_code) +
                                               " does not match any requests");
        res.append<uint16_t>(_code);
        for (auto& arg: it->second)
        {
            if (dataSizes.at(arg) == Request::variableSize
                && arg != "players" && arg != "rooms")
                data.append<uint32_t>(_data.at(arg).size());
            data.append<Buffer>(_data.at(arg));
        }
        res.append<uint32_t>(data.size());
        res.append(data);
        return res;
    }

    /*
    ** Protected member function
    */
    void            Request::parse(Buffer const& raw)
    {
        size_t dataSize;

        clear();
        if (raw.size() < headerSize)
            throw Exception::IncompleteRequest("Buffer can't contain a \
                                                request header");
        _code    = raw.get<uint16_t>();
        dataSize = raw.get<uint32_t>(sizeof(uint16_t));
        if (raw.size() - headerSize < dataSize)
            throw Exception::IncompleteRequest("Buffer can't contain \
                                                request's data");
        parseData(raw, dataSize);
    }

    void            Request::parseData(Buffer const& raw, size_t dataSize)
    {
        Buffer                      tmp  = raw;
        size_t                      left = dataSize;
        LobbyReqMap::const_iterator it   =
                                            lobbyRequests
                                                    .find(static_cast<Code>(_code));

        tmp.consume(headerSize);
        if (it == lobbyRequests.end())
            throw Exception::NotImplemented("Request '" + std::to_string(_code)
                                            +
                                            "' does not exists or is not implemented");
        for (std::string const& arg: it->second)
        {
            auto   it = dataSizes.find(arg);
            size_t size;
            Buffer res;

            if (it == dataSizes.end())
                throw Exception::NotImplemented("Unknown data size: " + arg);
            if (arg == "rooms" || arg == "players")
            {
                _data.insert(std::make_pair(it->first, tmp));
                return;
            }
            if (it->second == variableSize)
            {
                size = tmp.get<uint32_t>();
                tmp.consume(sizeof(uint32_t));
                left -= sizeof(uint32_t);
            }
            else
                size = it->second;
            if (size > left)
                throw Exception::InvalidRequest("Request can't fit argument");
            if (size > tmp.size())
                throw Exception::IncompleteRequest("Buffer can't \
                                                    contain argument");
            res.setData(tmp.data(), size);
            tmp.consume(size);
            _data.insert(std::make_pair(it->first, res));
            left -= size;
        }
    }
}