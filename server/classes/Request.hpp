#ifndef REQUEST_HPP_
# define REQUEST_HPP_

# include <functional>
# include <vector>
# include <unordered_map>
# include "Buffer.hpp"
# include "IStringable.hpp"
# include "ValueError.hpp"
# include "Room.hpp"

namespace RType
{
    class Request : public IStringable
    {
    public:
        enum Protocol
        {
            PROTOCOL_UNSET,
            PROTOCOL_LOBBY,
            PROTOCOL_INGAME
        };

        enum LobbyRequest
        {
            LR_LISTROOMS    = 100,
            LR_CREATEROOM   = 101,
            LR_JOINROOM     = 102,
            LR_QUITROOM     = 103,
            LR_READY        = 201,
            LR_NOTREADY     = 202,
            LR_USERNAME     = 301,
            SE_LISTROOMS    = 400,
            SE_JOINROOM     = 401,
            SE_QUITROOM     = 402,
            SE_CLIENTRDY    = 403,
            SE_CLINOTRDY    = 404,
            SE_CLIUSRNM     = 405,
            SE_OK           = 601,
            SE_KO           = 602
        };

    public:
        typedef std::unordered_map<std::string, Buffer>     DataMap;
        typedef std::unordered_map<std::string, size_t>     DataSizeMap;
        typedef std::vector<std::string>                    DataArgs;
        typedef std::unordered_map<LobbyRequest, DataArgs,
                                    std::hash<uint16_t> >   LobbyReqMap;

    public:
        Request();
        Request(Protocol protocol, Buffer const& raw);
        virtual ~Request();

    public:
        Request(Request const& other);
        Request&        operator=(Request const& other);

    public:
        Protocol        getProtocol() const;
        uint16_t        getCode() const;
        size_t          size() const;

        template <typename Type>
        Type            get(std::string const& key) const
        {
            DataMap::const_iterator it = _data.find(key);

            if (it == _data.end())
                throw Exception::ValueError("No such data: " + key);
            return it->second.get<Type>();
        }

    protected:
        void            parse(Buffer const& raw);
        void            parseLobby(Buffer const& raw);
        void            parseInGame(Buffer const& raw);

    public:
        virtual std::string     toString() const;

    public:
        static const LobbyReqMap    lobbyRequests;
        static const DataSizeMap    dataSizes;
        static const uint16_t       unsetCode;
        static const size_t         variableSize;
        static const size_t         headerSize;

    protected:
        Protocol        _protocol;
        uint16_t        _code;
        size_t          _size;
        DataMap         _data;
    };

    template <>
    std::string     Request::get(std::string const& key) const;

    template <>
    RoomsCollection Request::get(std::string const& key) const;
}

#endif /* !REQUEST_HPP_ */
