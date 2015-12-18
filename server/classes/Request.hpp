#ifndef REQUEST_HPP_
# define REQUEST_HPP_

# include <functional>
# include <vector>
# include <unordered_map>
# include "Buffer.hpp"
# include "ValueError.hpp"
# include "ABasePacket.hpp"

namespace RType
{
    class Request : public ABasePacket
    {
    public:
        enum Code
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
            SE_ROOMINFO     = 406,
            SE_GAMESTART    = 500,
            SE_OK           = 601,
            SE_KO           = 602
        };

    public:
        struct Room
        {
            unsigned int    id;
            std::string     name;
            unsigned int    nbPlayers;
        };

        struct Player
        {
            unsigned int    id;
            std::string     username;
            bool            isReady;
        };

    public:
        typedef std::unordered_map<std::string, size_t>     DataSizeMap;
        typedef std::vector<std::string>                    DataArgs;
        typedef std::unordered_map<Code, DataArgs,
                                    std::hash<uint16_t> >   LobbyReqMap;
        typedef std::vector<Room>                           RoomsTab;
        typedef std::vector<Player>                         PlayersTab;

    public:
        Request(uint16_t code = 0);
        Request(Buffer const& raw);
        virtual ~Request();

    public:
        Request(Request const& other);
        Request&        operator=(Request const& other);

    protected:
        void            parse(Buffer const& raw);
        void            parseData(Buffer const& raw, size_t dataSize);

    public:
        template <typename Type>
        Type            get(std::string const& key) const
        {
            return ABasePacket::get<Type>(key);
        }

    public:
        virtual Buffer          toBuffer() const;
        virtual std::string     toString() const;

    public:
        static const LobbyReqMap    lobbyRequests;
        static const DataSizeMap    dataSizes;
        static const uint16_t       unsetCode;
        static const size_t         variableSize;
        static const size_t         headerSize;
    };

    template <>
    Request::RoomsTab       Request::get(std::string const& key) const;

    template <>
    Request::PlayersTab     Request::get(std::string const& key) const;
}

#endif /* !REQUEST_HPP_ */
