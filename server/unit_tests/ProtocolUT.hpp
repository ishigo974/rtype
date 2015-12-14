#ifndef PROTOCOLUT_HPP_
# define PROTOCOLUT_HPP_

# include <string>
# include "ABaseUT.hpp"
# include "Request.hpp"
# include "Buffer.hpp"
# include "TcpConnector.hpp"

namespace RType
{
    class ProtocolUT : public UnitTesting::ABaseUT
    {
    public:
        ProtocolUT(std::string const& ip, short int port);
        virtual ~ProtocolUT();

    private:
        ProtocolUT(ProtocolUT const& other) = delete;
        ProtocolUT&             operator=(ProtocolUT const& other) = delete;

    protected:
        static void             lobbyRequestParsingWithoutData();
        static void             lobbyRequestParsingWithData();
        static void             createSingleRoomAndList();

    protected:
        static Buffer           receiveAll(TcpConnector& client);
        static Buffer           formatRequest(Request::LobbyRequest code,
                                              Buffer const& data = Buffer());

    public:
        virtual void            registerTests();
        virtual std::string     getName() const;

    protected:
        static std::string      ip;
        static short int        port;
    };
}

#endif /* !PROTOCOLUT_HPP_ */