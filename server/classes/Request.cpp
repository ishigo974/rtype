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
    const uint16_t                  Request::unsetCode      = 0;
    const size_t                    Request::variableSize   = 0;
    const size_t                    Request::headerSize     = sizeof(uint16_t) +
                                                              sizeof(uint32_t);
    const Request::LobbyReqMap      Request::lobbyRequests  = {
        { LR_LISTROOMS,     {}                          },
        { LR_CREATEROOM,    { "room_name" }             },
        { LR_JOINROOM,      { "room_id" }               },
        { LR_QUITROOM,      {}                          },
        { LR_READY,         {}                          },
        { LR_NOTREADY,      {}                          },
        { LR_USERNAME,      { "username"}               },
        { SE_LISTROOMS,     { "rooms" }                 },
        { SE_JOINROOM,      { "player_id", "username" } },
        { SE_CLIUSRNM,      { "player_id", "username" } },
        { SE_CLIENTRDY,     { "player_id" }             },
        { SE_CLINOTRDY,     { "player_id" }             },
        { SE_GAMESTART,     {}                          },
        { SE_ROOMINFO,      { "player_id", "players" }  },
        { SE_OK,            {}                          }
    };
    const Request::DataSizeMap      Request::dataSizes  = {
        { "size",       sizeof(uint32_t)        },
        { "room_name",  Request::variableSize   },
        { "room_id",    sizeof(uint32_t)        },
        { "username",   Request::variableSize   },
        { "rooms",      Request::variableSize   },
        { "player_id",  sizeof(uint8_t)         },
        { "players",    Request::variableSize   }
    };

    /*
    ** Constructor/Destructor
    */
    Request::Request() : _code(unsetCode), _size(0)
    {
    }

    Request::Request(Buffer const& raw) :
        _code(unsetCode), _size(0)
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
        _code(other._code),
        _size(other._size), _data(other._data)
    {
    }

    Request&        Request::operator=(Request const& other)
    {
        if (this != &other)
        {
            _code = other._code;
            _size = other._size;
            _data = other._data;
        }
        return *this;
    }

    /*
    ** Public member functions
    */
    template <>
    std::string         Request::get(std::string const& key) const
    {
        DataMap::const_iterator it = _data.find(key);

        if (it == _data.end())
            throw std::runtime_error("no such data: " + key); // TODO
        return it->second.getString();
    }

    template <>
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
            Room            room;
            uint32_t        size;

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

    template <>
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
            Player      player;
            uint32_t    size;

            player.id = buffer.get<uint8_t>();
            buffer.consume(sizeof(uint8_t));
            size = buffer.get<uint32_t>();
            buffer.consume(sizeof(uint32_t));
            player.username = buffer.getString(size);
            buffer.consume(size);
            player.isReady = buffer.get<uint8_t>();
            buffer.consume(sizeof(uint8_t));
            players.push_back(player);
        }
        return players;
    }

    uint16_t            Request::getCode() const
    {
        return _code;
    }

    size_t              Request::size() const
    {
        return _size;
    }

    std::string         Request::toString() const
    {
        std::ostringstream  ss;

        ss << "Request {"
            << "\n\t_code: " << _code
            << "\n\t_size: " << _size
            << "\n\tnb data: " << _data.size()
            << "\n}\n";
        return ss.str();
    }

    /*
    ** Protected member function
    */
    void            Request::parse(Buffer const& raw)
    {
        size_t      dataSize;

        if (raw.size() < headerSize)
            throw Exception::IncompleteRequest("Buffer can't contain a \
                                                request header");
        _code = raw.get<uint16_t>();
        dataSize = raw.get<uint32_t>(sizeof(uint16_t));
        _size = headerSize + dataSize;
        if (raw.size() - headerSize < dataSize)
            throw Exception::IncompleteRequest("Buffer can't contain \
                                                request's data");
        parseData(raw);
    }

    void            Request::parseData(Buffer const& raw)
    {
        Buffer                          tmp = raw;
        size_t                          left = _size - headerSize;
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
            if (arg == "rooms" || arg == "players")
            {
                _data.insert(std::make_pair(it->first, tmp));
                return ;
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
