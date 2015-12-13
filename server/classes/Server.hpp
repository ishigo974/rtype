#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <string>
# include <vector>
# include <unordered_map>
# include <utility>
# include "EntityManager.hpp"
# include "SystemManager.hpp"
# include "SocketMonitor.hpp"
# include "TcpAcceptor.hpp"

namespace RType
{
    class Server : public IStringable
    {
    public:
        typedef std::vector<std::string>    ArgsTab;
        typedef void    (Server::*CLICMDHandler)(ArgsTab const& args);
        typedef std::unordered_map<std::string,
                    std::pair<std::string, CLICMDHandler> >  CLICMDHandlers;

    public:
        enum Response
        {
            LOBBY_LISTROOMS = 400,
            LOBBY_JOINROOM  = 401,
            LOBBY_QUITROOM  = 402,
            LOBBY_CLIENTRDY = 403,
            LOBBY_CLINOTRDY = 404,
            LOBBY_CLIUSRNM  = 405,
            LOBBY_OK        = 601,
            LOBBY_KO        = 602
        };

    public:
        Server();
        Server(short int port);
        virtual ~Server();

    private:
        Server(Server const& other) = delete;
        Server&         operator=(Server const& other) = delete;

    public:
        void            run();
        void            notifyDisconnected(unsigned int id);

    protected:
        void            init();
        void            onClientConnection();
        void            onCLICommand();
        void            checkDisconnected();

    protected:
        void            handleCLIHelp(ArgsTab const& args);
        void            handleCLIRooms(ArgsTab const& args);
        void            handleCLIClients(ArgsTab const& args);
        void            handleCLIQuit(ArgsTab const& args);

    public:
        virtual std::string     toString() const;

    public:
        static void             display(std::string const& msg,
                                        bool err = false);

    protected:
        static Buffer           getResponseOK();
        static Buffer           getResponseKO();

    public:
        static const short int      defaultPort;
        static const Buffer         responseOK;
        static const Buffer         responseKO;
        static const unsigned int   stdinFileNo;
        static const CLICMDHandlers cliCmdHandlers;

    protected:
        bool                        _quit;
        TcpAcceptor                 _acceptor;
        SocketMonitor&              _monitor;
        ECS::EntityManager&         _em;
        ECS::SystemManager&         _sm;
        std::vector<unsigned int>   _disconnected;
    };
}

#endif /* !SERVER_HPP_ */
